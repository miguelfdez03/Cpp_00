#include "RobotomyRequestForm.hpp"
#include "Bureaucrat.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

// ── Default constructor ───────────────────────────────────────────────────────
RobotomyRequestForm::RobotomyRequestForm(void)
	: AForm("RobotomyRequestForm", 72, 45), _target("default")
{}

// ── Target constructor ────────────────────────────────────────────────────────
RobotomyRequestForm::RobotomyRequestForm(std::string const& target)
	: AForm("RobotomyRequestForm", 72, 45), _target(target)
{}

// ── Copy constructor ──────────────────────────────────────────────────────────
RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm const& other)
	: AForm(other), _target(other._target)
{}

// ── Copy assignment operator ──────────────────────────────────────────────────
RobotomyRequestForm& RobotomyRequestForm::operator=(RobotomyRequestForm const& other)
{
	if (this != &other)
	{
		AForm::operator=(other);
		_target = other._target;
	}
	return *this;
}

// ── Destructor ────────────────────────────────────────────────────────────────
RobotomyRequestForm::~RobotomyRequestForm(void)
{}

// ── doExecute ─────────────────────────────────────────────────────────────────
// Makes drilling noises, then robotomizes target 50% of the time.
void RobotomyRequestForm::doExecute(Bureaucrat const& executor) const
{
	(void)executor;
	std::cout << "Drrrrrr... BZZZZZT... KRRRR... *drilling noises*" << std::endl;
	if (std::rand() % 2 == 0)
		std::cout << _target << " has been robotomized successfully!" << std::endl;
	else
		std::cout << _target << " robotomization failed." << std::endl;
}

