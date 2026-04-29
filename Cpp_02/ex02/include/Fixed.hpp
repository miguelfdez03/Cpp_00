#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed
{
private:
    int                 _raw;
    static const int    _fractBits;
public:
    Fixed();
    Fixed(int const n);
    Fixed(float const f);
    Fixed(Fixed const & other);
    Fixed &operator=(Fixed const & other);
    ~Fixed();

    int getRawBits(void) const;
    void setRawBits(int const raw);

    int toInt(void) const;
    float toFloat(void) const;

    // Comparison operators
    bool operator>(Fixed const &other) const;
    bool operator<(Fixed const &other) const;
    bool operator>=(Fixed const &other) const;
    bool operator<=(Fixed const &other) const;
    bool operator==(Fixed const &other) const;
    bool operator!=(Fixed const &other) const;

    // Arithmetic operators
    Fixed operator+(Fixed const &other) const;
    Fixed operator-(Fixed const &other) const;
    Fixed operator*(Fixed const &other) const;
    Fixed operator/(Fixed const &other) const;

    // Increment / decrement
    Fixed &operator++();   // pre-increment
    Fixed operator++(int); // post-increment
    Fixed &operator--();
    Fixed operator--(int);

    static Fixed &min(Fixed &a, Fixed &b);
    static Fixed &max(Fixed &a, Fixed &b);
    static Fixed const &min(Fixed const &a, Fixed const &b);
    static Fixed const &max(Fixed const &a, Fixed const &b);
};

std::ostream &operator<<(std::ostream &os, Fixed const &f);

#endif // FIXED_HPP
