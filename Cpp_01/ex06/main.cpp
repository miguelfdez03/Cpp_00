#include "Harl.hpp"
#include <iostream>
#include <string>

int main(int argc, char **argv)
{
    Harl harl;
    if (argc != 2) {
        std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
        return 0;
    }
    std::string level = argv[1];
    std::string levels[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};
    int i = 0;
    for (; i < 4 && levels[i] != level; ++i);
    if (i == 4) {
        std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
        return 0;
    }
    harl.complainFrom(i);
    return 0;
}
