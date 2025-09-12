#include <iostream>
#include <string>
#include <limits>

int main()
{
	std::string name = "Hola";
	std::string get;

    int* p = new int(65);
    char* ch = reinterpret_cast<char*>(p);

	std::cout << name << std::endl;
	std::cin >> get;
	std::cout << std::endl;
	std::cout << get;

    // Reinterpret_cast
    std::cout << *p << " ," << p << std::endl << *ch << " ," << ch << std::endl; 
    

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();

	return 0;
}
