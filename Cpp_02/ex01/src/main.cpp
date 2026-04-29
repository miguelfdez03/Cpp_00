#include "../include/Fixed.hpp"
#include <iostream>

int main()
{
    Fixed a(5);
    Fixed b(3.25f);
    Fixed c(b);

    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "c = " << c << std::endl;

    return 0;
}
