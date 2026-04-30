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
	Fixed(Fixed const &other);
	Fixed &operator=(Fixed const &other);
	~Fixed();

	int getfixedPointNumber(void) const;
	void setfixedPointNumber(int const fixedPointNumber);
};

#endif
