```c++
#include <iostream>
#include <memory>
#include <string>
#include <variant>

// =======================
// 1) Data classes
// =======================
struct UserData {
    int id;
    std::string name;
};

struct OrderData {
    int orderId;
    double amount;
};

// =======================
// 2) API interface por tipo (polimorfismo paramétrico)
// =======================
template <typename T>
struct IApi {
    virtual ~IApi() = default;
    virtual void send(const T& data) = 0;
};

// =======================
// 3) Implementaciones concretas
// =======================
struct UserApi : IApi<UserData> {
    void send(const UserData& u) override {
        std::cout << "[UserApi] POST /users  {id:" << u.id
                  << ", name:\"" << u.name << "\"}\n";
    }
};

struct OrderApi : IApi<OrderData> {
    void send(const OrderData& o) override {
        std::cout << "[OrderApi] POST /orders {orderId:" << o.orderId
                  << ", amount:" << o.amount << "}\n";
    }
};

// =======================
// 4) Traits: Tipo de dato -> Tipo de API
//    (solo especializas aquí para añadir nuevos tipos/APIs)
// =======================
template <typename T>
struct ApiFor; // no definida por defecto

template <>
struct ApiFor<UserData> {
    using type = UserApi;
};

template <>
struct ApiFor<OrderData> {
    using type = OrderApi;
};

// =======================
// 5) Factory principal
// =======================
template <typename T>
std::unique_ptr<IApi<T>> make_api() {
    static_assert(!std::is_void_v<typename ApiFor<T>::type>,
                  "ApiFor<T> no especializado para este tipo T");
    using Impl = typename ApiFor<T>::type;
    return std::make_unique<Impl>();
}

// =======================
// 6) Uso en runtime con std::variant (datos dinámicos)
// =======================
using AnyData = std::variant<UserData, OrderData>;

void send_any(const AnyData& data) {
    std::visit([](auto&& value) {
        using T = std::decay_t<decltype(value)>;
        auto api = make_api<T>();     // elige la API por el tipo real en variant
        api->send(value);
    }, data);
}

// =======================
// 7) Demo
// =======================
int main() {
    // --- Compile-time: conozco el tipo ---
    UserData u{42, "Lulu"};
    auto userApi = make_api<UserData>();
    userApi->send(u);

    OrderData o{1001, 259.99};
    auto orderApi = make_api<OrderData>();
    orderApi->send(o);

    // --- Runtime: el tipo llega dinámicamente ---
    AnyData any1 = u;
    AnyData any2 = o;
    send_any(any1);
    send_any(any2);

    // Extender con un nuevo tipo sería:
    // 1) definir struct ProductData {...}
    // 2) definir struct ProductApi : IApi<ProductData> { void send(...) override; }
    // 3) especializar template<> struct ApiFor<ProductData> { using type = ProductApi; }
    // Nada más cambia.
}

```