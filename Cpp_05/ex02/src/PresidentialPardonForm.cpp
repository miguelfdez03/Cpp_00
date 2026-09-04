#include "PresidentialPardonForm.hpp"
#include "Bureaucrat.hpp"
#include <iostream>

// ── Default constructor ───────────────────────────────────────────────────────
PresidentialPardonForm::PresidentialPardonForm(void)
	: AForm("PresidentialPardonForm", 25, 5), _target("default")
{}

// ── Target constructor ────────────────────────────────────────────────────────
PresidentialPardonForm::PresidentialPardonForm(std::string const& target)
	: AForm("PresidentialPardonForm", 25, 5), _target(target)
{}

// ── Copy constructor ──────────────────────────────────────────────────────────
PresidentialPardonForm::PresidentialPardonForm(PresidentialPardonForm const& other)
	: AForm(other), _target(other._target)
{}

// ── Copy assignment operator ──────────────────────────────────────────────────
PresidentialPardonForm& PresidentialPardonForm::operator=(PresidentialPardonForm const& other)
{
	if (this != &other)
	{
		AForm::operator=(other);
		_target = other._target;
	}
	return *this;
}

// ── Destructor ────────────────────────────────────────────────────────────────
PresidentialPardonForm::~PresidentialPardonForm(void)
{}

// ── doExecute ─────────────────────────────────────────────────────────────────
void PresidentialPardonForm::doExecute(Bureaucrat const& executor) const
{
	(void)executor;
	std::cout << _target << " has been pardoned by Zaphod Beeblebrox." << std::endl;
}

