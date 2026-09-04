#include "AForm.hpp"
#include "Bureaucrat.hpp"

// ── Default constructor ───────────────────────────────────────────────────────
AForm::AForm(void)
	: _name("default"), _isSigned(false), _gradeToSign(75), _gradeToExecute(75)
{}

// ── Parameterized constructor ─────────────────────────────────────────────────
AForm::AForm(std::string const& name, int gradeToSign, int gradeToExecute)
	: _name(name), _isSigned(false),
	  _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
{
	if (_gradeToSign < 1 || _gradeToExecute < 1)
		throw AForm::GradeTooHighException();
	if (_gradeToSign > 150 || _gradeToExecute > 150)
		throw AForm::GradeTooLowException();
}

// ── Copy constructor ──────────────────────────────────────────────────────────
AForm::AForm(AForm const& other)
	: _name(other._name), _isSigned(other._isSigned),
	  _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute)
{}

// ── Copy assignment operator ──────────────────────────────────────────────────
AForm& AForm::operator=(AForm const& other)
{
	if (this != &other)
		_isSigned = other._isSigned;
	return *this;
}

// ── Destructor ────────────────────────────────────────────────────────────────
AForm::~AForm(void)
{}

// ── Getters ───────────────────────────────────────────────────────────────────
std::string const& AForm::getName(void) const
{
	return _name;
}

bool AForm::getIsSigned(void) const
{
	return _isSigned;
}

int AForm::getGradeToSign(void) const
{
	return _gradeToSign;
}

int AForm::getGradeToExecute(void) const
{
	return _gradeToExecute;
}

// ── beSigned ──────────────────────────────────────────────────────────────────
void AForm::beSigned(Bureaucrat const& b)
{
	if (b.getGrade() > _gradeToSign)
		throw AForm::GradeTooLowException();
	_isSigned = true;
}

// ── execute ───────────────────────────────────────────────────────────────────
// Centralized checks: verifies the form is signed and the executor's grade
// is sufficient before delegating the actual action to doExecute().
// This is the "elegant" design referred to by the subject.
void AForm::execute(Bureaucrat const& executor) const
{
	if (!_isSigned)
		throw AForm::FormNotSignedException();
	if (executor.getGrade() > _gradeToExecute)
		throw AForm::GradeTooLowToExecuteException();
	doExecute(executor);
}

// ── Exception messages ────────────────────────────────────────────────────────
const char* AForm::GradeTooHighException::what(void) const throw()
{
	return "Form grade is too high (minimum grade is 1)";
}

const char* AForm::GradeTooLowException::what(void) const throw()
{
	return "Bureaucrat's grade is too low to sign this form";
}

const char* AForm::FormNotSignedException::what(void) const throw()
{
	return "Form has not been signed yet";
}

const char* AForm::GradeTooLowToExecuteException::what(void) const throw()
{
	return "Bureaucrat's grade is too low to execute this form";
}

// ── operator<< ────────────────────────────────────────────────────────────────
std::ostream& operator<<(std::ostream& os, AForm const& f)
{
	os << "AForm [" << f.getName() << "]"
	   << " | signed: "          << (f.getIsSigned() ? "yes" : "no")
	   << " | grade to sign: "   << f.getGradeToSign()
	   << " | grade to execute: "<< f.getGradeToExecute();
	return os;
}

