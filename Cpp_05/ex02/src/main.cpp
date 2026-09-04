#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
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

	// ── TEST 1: ShrubberyCreationForm — full happy path ───────────────────
	printSeparator("TEST 1: ShrubberyCreationForm (sign 145, exec 137)");
	try
	{
		ShrubberyCreationForm scf("garden");
		Bureaucrat            gardener("Gardener", 130);

		std::cout << scf << std::endl;
		gardener.signForm(scf);
		gardener.executeForm(scf); // creates garden_shrubbery
	}
	catch (std::exception& e)
	{
		std::cout << "Unexpected exception: " << e.what() << std::endl;
	}

	// ── TEST 2: Execute unsigned form → FormNotSignedException ────────────
	printSeparator("TEST 2: Execute unsigned form");
	try
	{
		ShrubberyCreationForm scf("forest");
		Bureaucrat            b("Worker", 1);

		b.executeForm(scf); // not signed → error message
	}
	catch (std::exception& e)
	{
		std::cout << "Unexpected exception: " << e.what() << std::endl;
	}

	// ── TEST 3: Execute with insufficient grade ───────────────────────────
	printSeparator("TEST 3: executeForm grade too low");
	try
	{
		ShrubberyCreationForm scf("park");
		Bureaucrat            signer("Signer", 140);
		Bureaucrat            weakExec("WeakExec", 138); // exec requires 137

		signer.signForm(scf);
		weakExec.executeForm(scf); // grade 138 > 137 required → error
	}
	catch (std::exception& e)
	{
		std::cout << "Unexpected exception: " << e.what() << std::endl;
	}

	// ── TEST 4: RobotomyRequestForm — multiple executions (50/50) ─────────
	printSeparator("TEST 4: RobotomyRequestForm (sign 72, exec 45)");
	try
	{
		RobotomyRequestForm rrf("Bender");
		Bureaucrat          dr("Dr. Robotnik", 40);

		dr.signForm(rrf);
		dr.executeForm(rrf);
		dr.executeForm(rrf);
		dr.executeForm(rrf);
		dr.executeForm(rrf);
	}
	catch (std::exception& e)
	{
		std::cout << "Unexpected exception: " << e.what() << std::endl;
	}

	// ── TEST 5: PresidentialPardonForm — happy path ───────────────────────
	printSeparator("TEST 5: PresidentialPardonForm (sign 25, exec 5)");
	try
	{
		PresidentialPardonForm ppf("Arthur Dent");
		Bureaucrat             president("President", 1);

		president.signForm(ppf);
		president.executeForm(ppf);
	}
	catch (std::exception& e)
	{
		std::cout << "Unexpected exception: " << e.what() << std::endl;
	}

	// ── TEST 6: Bureaucrat grade too low to SIGN PresidentialPardonForm ───
	printSeparator("TEST 6: Grade too low to sign PresidentialPardonForm");
	try
	{
		PresidentialPardonForm ppf("Marvin");
		Bureaucrat             intern("Intern", 50); // 50 > 25 required

		intern.signForm(ppf);    // prints "couldn't sign"
		intern.executeForm(ppf); // prints "couldn't execute" (not signed)
	}
	catch (std::exception& e)
	{
		std::cout << "Unexpected exception: " << e.what() << std::endl;
	}

	// ── TEST 7: Polymorphism — AForm pointer, delete via base ─────────────
	printSeparator("TEST 7: Polymorphism via AForm*");
	try
	{
		AForm*     forms[3];
		Bureaucrat alpha("Alpha", 1);

		forms[0] = new ShrubberyCreationForm("poly");
		forms[1] = new RobotomyRequestForm("PolyBot");
		forms[2] = new PresidentialPardonForm("PolyDent");

		for (int i = 0; i < 3; i++)
		{
			alpha.signForm(*forms[i]);
			alpha.executeForm(*forms[i]);
		}

		for (int i = 0; i < 3; i++)
			delete forms[i]; // virtual destructor ensures correct cleanup
	}
	catch (std::exception& e)
	{
		std::cout << "Unexpected exception: " << e.what() << std::endl;
	}

	// ── TEST 8: operator<< on all three concrete forms ────────────────────
	printSeparator("TEST 8: operator<< on concrete forms");
	{
		ShrubberyCreationForm  scf("display");
		RobotomyRequestForm    rrf("display");
		PresidentialPardonForm ppf("display");

		std::cout << scf << std::endl;
		std::cout << rrf << std::endl;
		std::cout << ppf << std::endl;
	}

	std::cout << "\n══════════════════════════════════════" << std::endl;
	std::cout << "  All ex02 tests completed." << std::endl;
	std::cout << "══════════════════════════════════════\n" << std::endl;

	return 0;
}

