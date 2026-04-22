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
    int idx = -1;
    std::string levels[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};
    for (int i = 0; i < 4; ++i) {
        if (levels[i] == level) {
            idx = i;
            break;
        }
    }
    if (idx == -1) {
        std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
        return 0;
    }
    harl.complainFrom(idx);
    return 0;
}
