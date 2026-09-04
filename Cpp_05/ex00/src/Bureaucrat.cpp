#include "Bureaucrat.hpp"

// ── Default constructor ───────────────────────────────────────────────────────
Bureaucrat::Bureaucrat(void) : _name("default"), _grade(75)
{}

// ── Parameterized constructor ─────────────────────────────────────────────────
// Throws before the object is fully constructed if grade is invalid.
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
// _name is const and cannot be reassigned; only _grade is updated.
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
std::string const& Bureaucrat::getName(void) const
{
	return _name;
}

int Bureaucrat::getGrade(void) const
{
	return _grade;
}

// ── incrementGrade ────────────────────────────────────────────────────────────
// Moves the grade toward 1 (higher authority). grade 3 → grade 2.
// Throws GradeTooHighException if already at grade 1.
void Bureaucrat::incrementGrade(void)
{
	if (_grade - 1 < 1)
		throw Bureaucrat::GradeTooHighException();
	_grade--;
}

// ── decrementGrade ────────────────────────────────────────────────────────────
// Moves the grade toward 150 (lower authority). grade 3 → grade 4.
// Throws GradeTooLowException if already at grade 150.
void Bureaucrat::decrementGrade(void)
{
	if (_grade + 1 > 150)
		throw Bureaucrat::GradeTooLowException();
	_grade++;
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
// Format: "<name>, bureaucrat grade <grade>."
std::ostream& operator<<(std::ostream& os, Bureaucrat const& b)
{
	os << b.getName() << ", bureaucrat grade " << b.getGrade() << ".";
	return os;
}

