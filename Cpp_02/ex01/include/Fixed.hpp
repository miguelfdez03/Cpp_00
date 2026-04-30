#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>

class Fixed
{
private:
	int _fixedPointNumber;
	static const int _fractBits = 8;

public:
	Fixed();
	Fixed(int const n);
	Fixed(float const f);
	Fixed(Fixed const &other);
	Fixed &operator=(Fixed const &other);
	~Fixed();

	int getRawBits(void) const;
	void setRawBits(int const raw);
	float toFloat(void) const;
	int toInt(void) const;
};

std::ostream &operator<<(std::ostream &os, Fixed const &f);

#endif
