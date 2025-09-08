// Run Time Type Identification(RTTI)
#include <iostream>

// initialization of base class
class Base {
    public:
        virtual void polymorf () {
            std::cout << "LULU POLIMOOOOORF" << std::endl;
        }
        virtual ~Base() = default;
            
};

// initialization of derived class
class Derived : public Base {
    public:
    void polymorf() {
        std::cout << "LULU DIES..." << std::endl;
    }
};

// Driver Code
int main() {
    Base* point_derived = new Derived; // Base class pointers to 

    Derived* d = dynamic_cast<Derived*>(point_derived); // Derived class pointer

    if (d != nullptr) {
        d->polymorf();
    } 
    else {
        std::cout << "cannot cast B* to D*";
    }

    delete point_derived;
    return 0;
}

