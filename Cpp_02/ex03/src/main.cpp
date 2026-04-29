#include "../include/Point.hpp"
#include <iostream>

int main()
{
    Point a(0, 0);
    Point b(10, 0);
    Point c(0, 10);
    Point p(1, 1);

    std::cout << "Point inside triangle? " << (bsp(a,b,c,p) ? "yes" : "no") << std::endl;
    return 0;
}
