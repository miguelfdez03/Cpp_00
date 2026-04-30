#include "../include/Fixed.hpp"
#include <iostream>

int	main(void)
{
	Fixed	c;

	Fixed a(2);
	Fixed b(3);
	c = a * b;
	std::cout << "a = " << a << std::endl;
	std::cout << "b = " << b << std::endl;
	std::cout << "c = a * b = " << c << std::endl;
	return (0);
}
