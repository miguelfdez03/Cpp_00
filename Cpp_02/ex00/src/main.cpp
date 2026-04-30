#include "../include/Fixed.hpp"

int	main(void)
{
	Fixed	a;
	Fixed	c;

	Fixed b(a);
	c = b;
	(void)a;
	(void)b;
	(void)c;
	return (0);
}
