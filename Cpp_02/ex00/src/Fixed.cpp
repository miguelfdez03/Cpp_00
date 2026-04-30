#include "../include/Fixed.hpp"
#include <iostream>

Fixed::Fixed() : _fixedPointNumber(0)
{
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(Fixed const &other)
{
	std::cout << "Copy constructor called" << std::endl;
	*this = other;
}

Fixed &Fixed::operator=(Fixed const &other)
{
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &other)
		this->_fixedPointNumber = other.getfixedPointNumber();
	return (*this);
}

Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}

int Fixed::getfixedPointNumber(void) const
{
	std::cout << "getfixedPointNumber member function called" << std::endl;
	return (this->_fixedPointNumber);
}

void Fixed::setfixedPointNumber(int const raw)
{
	this->_fixedPointNumber = raw;
}
