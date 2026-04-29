#ifndef POINT_HPP
#define POINT_HPP

#include "../../Cpp_02/ex02/include/Fixed.hpp"

class Point
{
private:
    Fixed const _x;
    Fixed const _y;
public:
    Point();
    Point(float x, float y);
    Point(Point const &other);
    Point &operator=(Point const &other);
    ~Point();

    Fixed getX(void) const;
    Fixed getY(void) const;
};

bool bsp(Point const a, Point const b, Point const c, Point const point);

#endif // POINT_HPP
