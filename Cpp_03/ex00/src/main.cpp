#include "../include/ClapTrap.hpp"
#include <iostream>

int	main(void)
{
	ClapTrap a("Alpha");
	a.attack("target1");
	a.takeDamage(5);
	a.beRepaired(3);
	a.takeDamage(20);
	a.attack("target2");
	return (0);
}
