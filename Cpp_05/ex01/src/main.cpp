#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>

static void printSeparator(std::string const& title)
{
	std::cout << "\n══════════════════════════════════════" << std::endl;
	std::cout << "  " << title << std::endl;
	std::cout << "══════════════════════════════════════" << std::endl;
}

int main(void)
{
	// ── TEST 1: Valid Form construction ───────────────────────────────────
	printSeparator("TEST 1: Valid Form construction");
	try
	{
		Form f1("Tax Return", 50, 25);
		std::cout << f1 << std::endl;

		Form f2("Top Secret", 1, 1);
		std::cout << f2 << std::endl;

		Form f3("Intern Memo", 150, 150);
		std::cout << f3 << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Unexpected exception: " << e.what() << std::endl;
	}

	// ── TEST 2: Form GradeTooHighException (gradeToSign = 0) ─────────────
	printSeparator("TEST 2: Form GradeTooHighException (gradeToSign 0)");
	try
	{
		Form invalid("Bad Form", 0, 50);
	}
	catch (Form::GradeTooHighException& e)
	{
		std::cout << "Caught Form::GradeTooHighException: " << e.what() << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Caught std::exception: " << e.what() << std::endl;
	}

	// ── TEST 3: Form GradeTooLowException (gradeToExecute = 151) ─────────
	printSeparator("TEST 3: Form GradeTooLowException (gradeToExecute 151)");
	try
	{
		Form invalid("Bad Form", 50, 151);
	}
	catch (Form::GradeTooLowException& e)
	{
		std::cout << "Caught Form::GradeTooLowException: " << e.what() << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Caught std::exception: " << e.what() << std::endl;
	}

	// ── TEST 4: Bureaucrat with sufficient grade signs the Form ───────────
	printSeparator("TEST 4: Successful signing");
	try
	{
		Form        f("Budget Approval", 50, 20);
		Bureaucrat  boss("Boss", 10); // grade 10 <= 50 required → can sign

		std::cout << "Before: " << f << std::endl;
		boss.signForm(f);             // prints "<boss> signed Budget Approval"
		std::cout << "After:  " << f << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Unexpected exception: " << e.what() << std::endl;
	}

	// ── TEST 5: Bureaucrat with insufficient grade fails to sign ──────────
	printSeparator("TEST 5: Failed signing (grade too low)");
	try
	{
		Form        f("Classified", 10, 5);
		Bureaucrat  intern("Intern", 100); // grade 100 > 10 required → cannot sign

		intern.signForm(f); // prints "<intern> couldn't sign Classified because ..."
		std::cout << "Form state: " << f << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Unexpected exception: " << e.what() << std::endl;
	}

	// ── TEST 6: beSigned() directly (catches as std::exception&) ─────────
	printSeparator("TEST 6: beSigned() catchable as std::exception&");
	try
	{
		Form       f("Directive", 5, 5);
		Bureaucrat lowly("Lowly", 150);
		f.beSigned(lowly); // must throw
	}
	catch (std::exception& e) // generic catch — eval requirement
	{
		std::cout << "Caught as std::exception&: " << e.what() << std::endl;
	}

	// ── TEST 7: operator<< shows complete Form state ──────────────────────
	printSeparator("TEST 7: operator<< complete Form state");
	try
	{
		Form       f("Annual Report", 30, 10);
		Bureaucrat b("Manager", 25);
		std::cout << "Unsigned: " << f << std::endl;
		b.signForm(f);
		std::cout << "Signed:   " << f << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Unexpected exception: " << e.what() << std::endl;
	}

	// ── TEST 8: Form Orthodox Canonical Form ──────────────────────────────
	printSeparator("TEST 8: Form Orthodox Canonical Form");
	try
	{
		Form original("Original", 40, 20);
		Form copy(original);               // copy constructor
		Form assigned("Assigned", 80, 40);

		Bureaucrat signer("Signer", 1);
		signer.signForm(original);         // sign original only

		assigned = original;               // copy assignment: _isSigned copies over

		std::cout << "Original : " << original  << std::endl;
		std::cout << "Copy     : " << copy      << std::endl; // not signed
		std::cout << "Assigned : " << assigned  << std::endl; // now signed
	}
	catch (std::exception& e)
	{
		std::cout << "Unexpected exception: " << e.what() << std::endl;
	}

	// ── TEST 9: Edge — exact grade boundary ───────────────────────────────
	printSeparator("TEST 9: Exact grade boundary (grade == gradeToSign)");
	try
	{
		Form       f("Boundary Form", 42, 10);
		Bureaucrat exact("Exact", 42); // grade == gradeToSign → should sign

		exact.signForm(f);
		std::cout << f << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Unexpected exception: " << e.what() << std::endl;
	}

	std::cout << "\n══════════════════════════════════════" << std::endl;
	std::cout << "  All ex01 tests completed." << std::endl;
	std::cout << "══════════════════════════════════════\n" << std::endl;

	return 0;
}

