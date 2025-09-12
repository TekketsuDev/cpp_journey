#include <iostream>

int main()
{
    int* p = new int(65);

    int* p_tocast = new int(22);

    // Reinterpret_cast
    
    std::cout << "====================CH=================" << std::endl;

    //char* ch = reinterpret_cast<char*>(p);

    std::cout << *p << " ," << p << std::endl;  
    
    std::cout << "===================P_TOCAST====================" << std::endl;
    
    std::cout << *p_tocast << " ," << p_tocast << std::endl << (char *)p << " ," << std::endl; 
    char* ch_p_tocast = reinterpret_cast<char*>(p_tocast);

    std::cout << "*ch_p_tocast: " << *ch_p_tocast 
              << " , ch_p_tocast (as address): " << static_cast<void*>(ch_p_tocast) 
              << " , as string: " << ch_p_tocast << std::endl;
    std::cout << "===================CH1====================" << std::endl;
    
    char* ch1 = (char*)p;
    
    std::cout << *p << " ," << p << std::endl << static_cast<void*>(ch1) << " ," << ch1 << std::endl;

    std::cout << "===================CH2====================" << std::endl;
    
    char* ch2 = reinterpret_cast<char*>(p); 
    
    std::cout << *p << " ," << p << std::endl << static_cast<void*>(ch2) << " ," << ch2 << " ," << *ch2 << std::endl;

	return 0;
}
