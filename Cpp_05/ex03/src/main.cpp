#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "Intern.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

static void printSeparator(std::string const& title)
{
	std::cout << "\n══════════════════════════════════════" << std::endl;
	std::cout << "  " << title << std::endl;
	std::cout << "══════════════════════════════════════" << std::endl;
}

int main(void)
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	Intern someRandomIntern;

	// ── TEST 1: Subject's own example — RobotomyRequestForm ──────────────
	printSeparator("TEST 1: Subject example (robotomy request / Bender)");
	{
		AForm* rrf = someRandomIntern.makeForm("robotomy request", "Bender");
		if (rrf)
		{
			Bureaucrat b("Technician", 40);
			b.signForm(*rrf);
			b.executeForm(*rrf);
			delete rrf;
		}
	}

	// ── TEST 2: ShrubberyCreationForm via Intern ──────────────────────────
	printSeparator("TEST 2: shrubbery creation / home");
	{
		AForm* scf = someRandomIntern.makeForm("shrubbery creation", "home");
		if (scf)
		{
			Bureaucrat b("Gardener", 130);
			b.signForm(*scf);
			b.executeForm(*scf);
			delete scf;
		}
	}

	// ── TEST 3: PresidentialPardonForm via Intern ─────────────────────────
	printSeparator("TEST 3: presidential pardon / Marvin");
	{
		AForm* ppf = someRandomIntern.makeForm("presidential pardon", "Marvin");
		if (ppf)
		{
			Bureaucrat president("President", 1);
			president.signForm(*ppf);
			president.executeForm(*ppf);
			delete ppf;
		}
	}

	// ── TEST 4: Unknown form name → error message, returns NULL ───────────
	printSeparator("TEST 4: Unknown form name");
	{
		AForm* unknown = someRandomIntern.makeForm("form 28B", "nobody");
		if (unknown)
		{
			std::cout << "ERROR: should have returned NULL" << std::endl;
			delete unknown;
		}
		else
			std::cout << "Correctly returned NULL for unknown form." << std::endl;
	}

	// ── TEST 5: All three forms — sign + execute via intern ───────────────
	printSeparator("TEST 5: All three forms in sequence");
	{
		const std::string names[3] = {
			"shrubbery creation",
			"robotomy request",
			"presidential pardon"
		};
		const std::string targets[3] = { "yard", "C3PO", "Ford Prefect" };

		Bureaucrat boss("Boss", 1); // grade 1: can sign and execute everything

		for (int i = 0; i < 3; i++)
		{
			AForm* form = someRandomIntern.makeForm(names[i], targets[i]);
			if (form)
			{
				boss.signForm(*form);
				boss.executeForm(*form);
				delete form;
			}
		}
	}

	// ── TEST 6: Intern OCF — copy constructor and operator= ──────────────
	printSeparator("TEST 6: Intern Orthodox Canonical Form");
	{
		Intern intern1;
		Intern intern2(intern1);   // copy constructor
		Intern intern3;
		intern3 = intern1;         // copy assignment

		// All three interns are equivalent — verify by using intern2 and intern3
		AForm* f2 = intern2.makeForm("presidential pardon", "Trillian");
		AForm* f3 = intern3.makeForm("robotomy request", "R2D2");

		if (f2) { std::cout << *f2 << std::endl; delete f2; }
		if (f3) { std::cout << *f3 << std::endl; delete f3; }
	}

	std::cout << "\n══════════════════════════════════════" << std::endl;
	std::cout << "  All ex03 tests completed." << std::endl;
	std::cout << "══════════════════════════════════════\n" << std::endl;

	return 0;
}

