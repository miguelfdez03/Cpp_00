#include "../include/FragTrap.hpp"
#include <iostream>

int main() {
    FragTrap f("Buddy");
    f.attack("box");
    f.takeDamage(20);
    f.beRepaired(5);
    f.highFivesGuys();
    return 0;
}
