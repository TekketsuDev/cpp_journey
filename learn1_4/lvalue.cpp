#include <iostream>

int main () {

   int value {32};

   int& ref {value};
   int refcopy {value};
 

    std::cout << "Before modification :" << std::endl;
    std::cout << "Reference its :" << ref << std::endl;
    std::cout << "Reference to val :" << refcopy << std::endl;
    value = 65;
    std::cout << "After modification :" << std::endl;
    std::cout << "Value its :" << value << std::endl;
    std::cout << "Reference its :" << ref << std::endl;
    std::cout << "Copy to val :" << refcopy << std::endl;


    return 0;
}
