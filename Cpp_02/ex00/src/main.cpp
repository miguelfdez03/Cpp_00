#include "../include/Fixed.hpp"

int main()
{
    Fixed a;
    Fixed b(a);
    Fixed c;
    c = b;

    (void)a; (void)b; (void)c; // placeholder to avoid unused warnings
    return 0;
}
