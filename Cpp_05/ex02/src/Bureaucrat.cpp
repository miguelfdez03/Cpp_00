#include "Bureaucrat.hpp"
#include "AForm.hpp"

// ── Default constructor ───────────────────────────────────────────────────────
Bureaucrat::Bureaucrat(void) : _name("default"), _grade(75)
{}

// ── Parameterized constructor ─────────────────────────────────────────────────
Bureaucrat::Bureaucrat(std::string const& name, int grade)
	: _name(name), _grade(grade)
{
	if (_grade < 1)
		throw Bureaucrat::GradeTooHighException();
	if (_grade > 150)
		throw Bureaucrat::GradeTooLowException();
}

// ── Copy constructor ──────────────────────────────────────────────────────────
Bureaucrat::Bureaucrat(Bureaucrat const& other)
	: _name(other._name), _grade(other._grade)
{}

// ── Copy assignment operator ──────────────────────────────────────────────────
Bureaucrat& Bureaucrat::operator=(Bureaucrat const& other)
{
	if (this != &other)
		_grade = other._grade;
	return *this;
}

// ── Destructor ────────────────────────────────────────────────────────────────
Bureaucrat::~Bureaucrat(void)
{}

// ── Getters ───────────────────────────────────────────────────────────────────
std::string const& Bureaucrat::getName(void) const { return _name; }
int                Bureaucrat::getGrade(void)  const { return _grade; }

// ── Grade manipulation ────────────────────────────────────────────────────────
void Bureaucrat::incrementGrade(void)
{
	if (_grade - 1 < 1)
		throw Bureaucrat::GradeTooHighException();
	_grade--;
}

void Bureaucrat::decrementGrade(void)
{
	if (_grade + 1 > 150)
		throw Bureaucrat::GradeTooLowException();
	_grade++;
}

// ── signForm ──────────────────────────────────────────────────────────────────
void Bureaucrat::signForm(AForm& form)
{
	try
	{
		form.beSigned(*this);
		std::cout << _name << " signed " << form.getName() << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << _name << " couldn't sign " << form.getName()
				  << " because " << e.what() << std::endl;
	}
}

// ── executeForm ───────────────────────────────────────────────────────────────
// Calls form.execute(*this). On success prints "<bureaucrat> executed <form>".
// On failure catches the exception and prints an explicit error message.
void Bureaucrat::executeForm(AForm const& form)
{
	try
	{
		form.execute(*this);
		std::cout << _name << " executed " << form.getName() << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << _name << " couldn't execute " << form.getName()
				  << " because " << e.what() << std::endl;
	}
}

// ── Exception messages ────────────────────────────────────────────────────────
const char* Bureaucrat::GradeTooHighException::what(void) const throw()
{
	return "Grade is too high (minimum grade is 1)";
}

const char* Bureaucrat::GradeTooLowException::what(void) const throw()
{
	return "Grade is too low (maximum grade is 150)";
}

// ── operator<< ────────────────────────────────────────────────────────────────
std::ostream& operator<<(std::ostream& os, Bureaucrat const& b)
{
	os << b.getName() << ", bureaucrat grade " << b.getGrade() << ".";
	return os;
}

