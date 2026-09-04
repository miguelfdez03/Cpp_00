#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"
#include <fstream>
#include <iostream>

// ── Default constructor ───────────────────────────────────────────────────────
ShrubberyCreationForm::ShrubberyCreationForm(void)
	: AForm("ShrubberyCreationForm", 145, 137), _target("default")
{}

// ── Target constructor ────────────────────────────────────────────────────────
ShrubberyCreationForm::ShrubberyCreationForm(std::string const& target)
	: AForm("ShrubberyCreationForm", 145, 137), _target(target)
{}

// ── Copy constructor ──────────────────────────────────────────────────────────
ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const& other)
	: AForm(other), _target(other._target)
{}

// ── Copy assignment operator ──────────────────────────────────────────────────
ShrubberyCreationForm& ShrubberyCreationForm::operator=(ShrubberyCreationForm const& other)
{
	if (this != &other)
	{
		AForm::operator=(other);
		_target = other._target;
	}
	return *this;
}

// ── Destructor ────────────────────────────────────────────────────────────────
ShrubberyCreationForm::~ShrubberyCreationForm(void)
{}

// ── doExecute ─────────────────────────────────────────────────────────────────
// Creates "<target>_shrubbery" file with ASCII trees.
// Grade and sign checks are already done by AForm::execute().
void ShrubberyCreationForm::doExecute(Bureaucrat const& executor) const
{
	(void)executor; // executor info not needed for this action
	std::string   filename = _target + "_shrubbery";
	std::ofstream file(filename.c_str());

	if (!file.is_open())
	{
		std::cerr << "Error: cannot create file " << filename << std::endl;
		return;
	}

	file << "        *        \n";
	file << "       ***       \n";
	file << "      *****      \n";
	file << "     *******     \n";
	file << "    *********    \n";
	file << "   ***********   \n";
	file << "  *************  \n";
	file << "       |||       \n";
	file << "       |||       \n";
	file << "                 \n";
	file << "    *            \n";
	file << "   ***           \n";
	file << "  *****          \n";
	file << " *******         \n";
	file << "   |||           \n";
	file << "   |||           \n";
	file << "                 \n";
	file << "            ***  \n";
	file << "           ***** \n";
	file << "          *******\n";
	file << "           *****  \n";
	file << "            ***  \n";
	file << "             |   \n";
	file << "             |   \n";

	file.close();
	std::cout << "Shrubbery created: " << filename << std::endl;
}
