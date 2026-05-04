#include "../include/ScavTrap.hpp"
#include <iostream>

ScavTrap::ScavTrap(std::string const & name): ClapTrap(name) {
    this->hitPoints = 100;
    this->energyPoints = 50;
    this->attackDamage = 20;
    std::cout << "ScavTrap " << this->name << " constructed" << std::endl;
}

ScavTrap::ScavTrap(ScavTrap const & other): ClapTrap(other) {
    *this = other;
    std::cout << "ScavTrap " << this->name << " copy-constructed" << std::endl;
}

ScavTrap & ScavTrap::operator=(ScavTrap const & other) {
    if (this != &other) {
        ClapTrap::operator=(other);
    }
    return *this;
}

ScavTrap::~ScavTrap() {
    std::cout << "ScavTrap " << this->name << " destructed" << std::endl;
}

void ScavTrap::attack(std::string const & target) {
    if (this->energyPoints == 0 || this->hitPoints == 0) {
        std::cout << "ScavTrap " << this->name << " cannot attack" << std::endl;
        return;
    }
    this->energyPoints--;
    std::cout << "ScavTrap " << this->name << " fiercely attacks " << target << ", causing " << this->attackDamage << " points of damage!" << std::endl;
}

void ScavTrap::guardGate() {
    std::cout << "ScavTrap " << this->name << " is now in Gate keeper mode." << std::endl;
}
