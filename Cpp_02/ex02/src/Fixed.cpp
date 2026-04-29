#include "../include/Fixed.hpp"
#include <iostream>

const int Fixed::_fractBits = 8;

Fixed::Fixed() : _raw(0) {}
Fixed::Fixed(int const n) : _raw(n << _fractBits) {}
Fixed::Fixed(float const f) : _raw(static_cast<int>(f * (1 << _fractBits))) {}
Fixed::Fixed(Fixed const & other) { *this = other; }
Fixed &Fixed::operator=(Fixed const & other) { if (this != &other) _raw = other.getRawBits(); return *this; }
Fixed::~Fixed() {}

int Fixed::getRawBits(void) const { return _raw; }
void Fixed::setRawBits(int const raw) { _raw = raw; }

int Fixed::toInt(void) const { return _raw >> _fractBits; }
float Fixed::toFloat(void) const { return static_cast<float>(_raw) / (1 << _fractBits); }

bool Fixed::operator>(Fixed const &other) const { return _raw > other._raw; }
bool Fixed::operator<(Fixed const &other) const { return _raw < other._raw; }
bool Fixed::operator>=(Fixed const &other) const { return _raw >= other._raw; }
bool Fixed::operator<=(Fixed const &other) const { return _raw <= other._raw; }
bool Fixed::operator==(Fixed const &other) const { return _raw == other._raw; }
bool Fixed::operator!=(Fixed const &other) const { return _raw != other._raw; }

Fixed Fixed::operator+(Fixed const &other) const { Fixed r; r.setRawBits(_raw + other._raw); return r; }
Fixed Fixed::operator-(Fixed const &other) const { Fixed r; r.setRawBits(_raw - other._raw); return r; }
Fixed Fixed::operator*(Fixed const &other) const { Fixed r; long tmp = static_cast<long>(_raw) * other._raw; r.setRawBits(static_cast<int>(tmp >> _fractBits)); return r; }
Fixed Fixed::operator/(Fixed const &other) const { Fixed r; long tmp = (static_cast<long>(_raw) << _fractBits) / other._raw; r.setRawBits(static_cast<int>(tmp)); return r; }

Fixed &Fixed::operator++() { _raw += 1; return *this; }
Fixed Fixed::operator++(int) { Fixed tmp(*this); _raw += 1; return tmp; }
Fixed &Fixed::operator--() { _raw -= 1; return *this; }
Fixed Fixed::operator--(int) { Fixed tmp(*this); _raw -= 1; return tmp; }

Fixed &Fixed::min(Fixed &a, Fixed &b) { return (a < b) ? a : b; }
Fixed &Fixed::max(Fixed &a, Fixed &b) { return (a > b) ? a : b; }
Fixed const &Fixed::min(Fixed const &a, Fixed const &b) { return (a < b) ? a : b; }
Fixed const &Fixed::max(Fixed const &a, Fixed const &b) { return (a > b) ? a : b; }

std::ostream &operator<<(std::ostream &os, Fixed const &f) { os << f.toFloat(); return os; }
