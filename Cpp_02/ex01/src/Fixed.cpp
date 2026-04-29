#include "../include/Fixed.hpp"
#include <iostream>

const int Fixed::_fractBits = 8;

Fixed::Fixed() : _raw(0)
{
    std::cout << "Default constructor called (ex01)" << std::endl;
}

Fixed::Fixed(int const n)
{
    std::cout << "Int constructor called" << std::endl;
    _raw = n << _fractBits; // placeholder behavior
}

Fixed::Fixed(float const f)
{
    std::cout << "Float constructor called" << std::endl;
    _raw = static_cast<int>(f * (1 << _fractBits)); // placeholder
}

Fixed::Fixed(Fixed const & other)
{
    std::cout << "Copy constructor called (ex01)" << std::endl;
    *this = other;
}

Fixed &Fixed::operator=(Fixed const & other)
{
    std::cout << "Copy assignment operator called (ex01)" << std::endl;
    if (this != &other)
        this->_raw = other.getRawBits();
    return *this;
}

Fixed::~Fixed()
{
    std::cout << "Destructor called (ex01)" << std::endl;
}

int Fixed::getRawBits(void) const
{
    return this->_raw;
}

void Fixed::setRawBits(int const raw)
{
    this->_raw = raw;
}

int Fixed::toInt(void) const
{
    return _raw >> _fractBits;
}

float Fixed::toFloat(void) const
{
    return static_cast<float>(_raw) / (1 << _fractBits);
}

std::ostream &operator<<(std::ostream &os, Fixed const &f)
{
    os << f.toFloat();
    return os;
}
