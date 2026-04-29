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
    Fixed(Fixed const & other);
    Fixed &operator=(Fixed const & other);
    ~Fixed();

    int getRawBits(void) const;
    void setRawBits(int const raw);
};

#endif // FIXED_HPP
