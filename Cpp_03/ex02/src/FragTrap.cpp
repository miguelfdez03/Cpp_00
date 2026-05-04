#include "../include/FragTrap.hpp"
#include <iostream>

FragTrap::FragTrap() : ClapTrap("Default_Frag")
{
	this->hitPoints = 100;
	this->energyPoints = 100;
	this->attackDamage = 30;
	std::cout << "FragTrap " << this->name << " constructed" << std::endl;
}

FragTrap::FragTrap(std::string const &name) : ClapTrap(name)
{
	this->hitPoints = 100;
	this->energyPoints = 100;
	this->attackDamage = 30;
	std::cout << "FragTrap " << this->name << " constructed" << std::endl;
}

FragTrap::FragTrap(FragTrap const &other) : ClapTrap(other)
{
	*this = other;
	std::cout << "FragTrap " << this->name << " copy-constructed" << std::endl;
}

FragTrap &FragTrap::operator=(FragTrap const &other)
{
	if (this != &other)
	{
		ClapTrap::operator=(other);
	}
	return (*this);
}

FragTrap::~FragTrap()
{
	std::cout << "FragTrap " << this->name << " destructed" << std::endl;
}

void FragTrap::highFivesGuys()
{
	std::cout << "FragTrap " << this->name << " requests a high five!" << std::endl;
}
