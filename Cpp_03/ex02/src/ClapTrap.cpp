#include "../include/ClapTrap.hpp"
#include <iostream>

ClapTrap::ClapTrap(std::string const & name): name(name), hitPoints(10), energyPoints(10), attackDamage(0) {
    std::cout << "ClapTrap " << this->name << " constructed" << std::endl;
}

ClapTrap::ClapTrap(ClapTrap const & other) {
    *this = other;
    std::cout << "ClapTrap " << this->name << " copy-constructed" << std::endl;
}

ClapTrap & ClapTrap::operator=(ClapTrap const & other) {
    if (this != &other) {
        this->name = other.name;
        this->hitPoints = other.hitPoints;
        this->energyPoints = other.energyPoints;
        this->attackDamage = other.attackDamage;
    }
    return *this;
}

ClapTrap::~ClapTrap() {
    std::cout << "ClapTrap " << this->name << " destructed" << std::endl;
}

void ClapTrap::attack(std::string const & target) {
    if (this->energyPoints == 0 || this->hitPoints == 0) {
        std::cout << "ClapTrap " << this->name << " cannot attack" << std::endl;
        return;
    }
    this->energyPoints--;
    std::cout << "ClapTrap " << this->name << " attacks " << target << ", causing " << this->attackDamage << " points of damage!" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount) {
    if (amount >= this->hitPoints)
        this->hitPoints = 0;
    else
        this->hitPoints -= amount;
    std::cout << "ClapTrap " << this->name << " takes " << amount << " points of damage (HP=" << this->hitPoints << ")" << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount) {
    if (this->energyPoints == 0 || this->hitPoints == 0) {
        std::cout << "ClapTrap " << this->name << " cannot be repaired" << std::endl;
        return;
    }
    this->energyPoints--;
    this->hitPoints += amount;
    std::cout << "ClapTrap " << this->name << " is repaired by " << amount << " (HP=" << this->hitPoints << ")" << std::endl;
}
