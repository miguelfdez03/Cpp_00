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
};

std::ostream &operator<<(std::ostream &os, Fixed const &f);

#endif // FIXED_HPP
