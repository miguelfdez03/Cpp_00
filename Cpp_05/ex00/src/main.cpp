#include "Bureaucrat.hpp"
#include <iostream>

// ── Helper: visual separator ──────────────────────────────────────────────────
static void printSeparator(std::string const& title)
{
	std::cout << "\n══════════════════════════════════════" << std::endl;
	std::cout << "  " << title << std::endl;
	std::cout << "══════════════════════════════════════" << std::endl;
}

int main(void)
{
	// ── TEST 1: Valid construction ────────────────────────────────────────
	printSeparator("TEST 1: Valid construction");
	try
	{
		Bureaucrat alice("Alice", 42);
		std::cout << alice << std::endl;

		Bureaucrat bob("Bob", 1);    // highest possible grade
		std::cout << bob << std::endl;

		Bureaucrat carol("Carol", 150); // lowest possible grade
		std::cout << carol << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Unexpected exception: " << e.what() << std::endl;
	}

	// ── TEST 2: GradeTooHighException on construction (grade 0) ──────────
	printSeparator("TEST 2: GradeTooHighException (grade 0)");
	try
	{
		Bureaucrat invalid("Invalid", 0);
		std::cout << invalid << std::endl; // should never reach here
	}
	catch (Bureaucrat::GradeTooHighException& e)
	{
		std::cout << "Caught GradeTooHighException: " << e.what() << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Caught std::exception: " << e.what() << std::endl;
	}

	// ── TEST 3: GradeTooLowException on construction (grade 151) ─────────
	printSeparator("TEST 3: GradeTooLowException (grade 151)");
	try
	{
		Bureaucrat invalid("Invalid", 151);
		std::cout << invalid << std::endl; // should never reach here
	}
	catch (Bureaucrat::GradeTooLowException& e)
	{
		std::cout << "Caught GradeTooLowException: " << e.what() << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Caught std::exception: " << e.what() << std::endl;
	}

	// ── TEST 4: incrementGrade direction (grade 3 → grade 2) ─────────────
	printSeparator("TEST 4: incrementGrade direction (3 -> 2)");
	try
	{
		Bureaucrat dave("Dave", 3);
		std::cout << "Before: " << dave << std::endl;
		dave.incrementGrade();
		std::cout << "After incrementGrade: " << dave << std::endl; // expect grade 2
	}
	catch (std::exception& e)
	{
		std::cout << "Unexpected exception: " << e.what() << std::endl;
	}

	// ── TEST 5: decrementGrade direction (grade 3 → grade 4) ─────────────
	printSeparator("TEST 5: decrementGrade direction (3 -> 4)");
	try
	{
		Bureaucrat eve("Eve", 3);
		std::cout << "Before: " << eve << std::endl;
		eve.decrementGrade();
		std::cout << "After decrementGrade: " << eve << std::endl; // expect grade 4
	}
	catch (std::exception& e)
	{
		std::cout << "Unexpected exception: " << e.what() << std::endl;
	}

	// ── TEST 6: GradeTooHighException on incrementGrade at grade 1 ───────
	printSeparator("TEST 6: incrementGrade throws at grade 1");
	try
	{
		Bureaucrat frank("Frank", 1);
		std::cout << frank << std::endl;
		frank.incrementGrade(); // must throw
		std::cout << frank << std::endl; // should never reach here
	}
	catch (Bureaucrat::GradeTooHighException& e)
	{
		std::cout << "Caught GradeTooHighException: " << e.what() << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Caught std::exception: " << e.what() << std::endl;
	}

	// ── TEST 7: GradeTooLowException on decrementGrade at grade 150 ──────
	printSeparator("TEST 7: decrementGrade throws at grade 150");
	try
	{
		Bureaucrat grace("Grace", 150);
		std::cout << grace << std::endl;
		grace.decrementGrade(); // must throw
		std::cout << grace << std::endl; // should never reach here
	}
	catch (Bureaucrat::GradeTooLowException& e)
	{
		std::cout << "Caught GradeTooLowException: " << e.what() << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Caught std::exception: " << e.what() << std::endl;
	}

	// ── TEST 8: Catchable as std::exception& (eval requirement) ──────────
	printSeparator("TEST 8: Exceptions catchable as std::exception&");
	try
	{
		Bureaucrat invalid("Invalid", -99);
	}
	catch (std::exception& e) // generic catch — must work per eval sheet
	{
		std::cout << "Caught as std::exception&: " << e.what() << std::endl;
	}

	// ── TEST 9: Copy constructor and operator= ────────────────────────────
	printSeparator("TEST 9: Orthodox Canonical Form");
	try
	{
		Bureaucrat original("Original", 10);
		Bureaucrat copy(original);          // copy constructor
		Bureaucrat assigned("Assigned", 50);
		assigned = original;                // copy assignment operator
		std::cout << "Original : " << original  << std::endl;
		std::cout << "Copy     : " << copy      << std::endl;
		std::cout << "Assigned : " << assigned  << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Unexpected exception: " << e.what() << std::endl;
	}

	// ── TEST 10: operator<< format check ─────────────────────────────────
	printSeparator("TEST 10: operator<< format");
	try
	{
		Bureaucrat henry("Henry", 7);
		// Expected: "Henry, bureaucrat grade 7."
		std::cout << henry << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Unexpected exception: " << e.what() << std::endl;
	}

	std::cout << "\n══════════════════════════════════════" << std::endl;
	std::cout << "  All ex00 tests completed." << std::endl;
	std::cout << "══════════════════════════════════════\n" << std::endl;

	return 0;
}

