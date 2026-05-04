#include "../include/Fixed.hpp"
#include <iostream>

Fixed::Fixed() : _fixedPointNumber(0)
{
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(int const n)
{
	std::cout << "Int constructor called" << std::endl;
	this->_fixedPointNumber = n << _fractBits;
}

Fixed::Fixed(float const f)
{
	float	scaled;

	std::cout << "Float constructor called" << std::endl;
	scaled = f * (1 << _fractBits);
	if (f >= 0)
		this->_fixedPointNumber = static_cast<int>(scaled + 0.5f);
	else
		this->_fixedPointNumber = static_cast<int>(scaled - 0.5f);
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
		this->_fixedPointNumber = other.getRawBits();
	return (*this);
}

Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}

int Fixed::getRawBits(void) const
{
	return (this->_fixedPointNumber);
}

void Fixed::setRawBits(int const raw)
{
	this->_fixedPointNumber = raw;
}

float Fixed::toFloat(void) const
{
	return (static_cast<float>(this->_fixedPointNumber) / (1 << _fractBits));
}

int Fixed::toInt(void) const
{
	return (this->_fixedPointNumber >> _fractBits);
}

std::ostream &operator<<(std::ostream &os, Fixed const &f)
{
	os << f.toFloat();
	return (os);
}
