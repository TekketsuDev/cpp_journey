#include <cstdint>
#include <iostream>

inline constexpr int MAX_COLOR = 255;

int main (){

    [[maybe_unused]] int a; // A declaration (unitialized)
    
    [[maybe_unused]] int b (5); // Direct initialization
    [[maybe_unused]] int c {5}; // Direct-list initialization (no narrowing)
    int d = 6; // Copy-Initialization with assignment operator
    int e = {7}; //Copy-list Initialization
    
    struct Color {
        std::uint8_t r{MAX_COLOR};
        std::uint8_t g{MAX_COLOR};
        std::uint8_t b{MAX_COLOR};
    };

    struct Apple {
        double weight{}; 
        Color color {}; //Value/Empty initialization
    };

    Apple imported_apple = { 12.4,{ 1, 3, 4}}; //Aggreate initialization -> copy-list-initialization
    Apple exported_apple { 14.4, {1, 3, 4}}; //Aggreate initialization -> direct-list-initialization

    Apple designated_apple { .weight {22},.color  = Color{ .g = 253 }}; //Designated Initializers

    std::cout << "exported weight = " << int(exported_apple.weight) << '\n';
    std::cout << "imported weight = " << int(imported_apple.weight) << '\n';
    std::cout << "imported apple red = " << int(imported_apple.color.r) << '\n';

    std::cout << "green apple = " << int(designated_apple.color.g) << '\n';
    std::cout << "green apple = " << int(designated_apple.color.b) << '\n';
    return 0;
}
