#include "../include/ScavTrap.hpp"
#include <iostream>

int main() {
    ScavTrap s("Guardian");
    s.attack("intruder");
    s.takeDamage(30);
    s.beRepaired(10);
    s.guardGate();
    return 0;
}
