#include "Form.hpp"
#include "Bureaucrat.hpp"

// ── Default constructor ───────────────────────────────────────────────────────
Form::Form(void)
	: _name("default"), _isSigned(false), _gradeToSign(75), _gradeToExecute(75)
{}

// ── Parameterized constructor ─────────────────────────────────────────────────
// Validates both grades before the object is considered fully constructed.
Form::Form(std::string const& name, int gradeToSign, int gradeToExecute)
	: _name(name), _isSigned(false),
	  _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
{
	if (_gradeToSign < 1 || _gradeToExecute < 1)
		throw Form::GradeTooHighException();
	if (_gradeToSign > 150 || _gradeToExecute > 150)
		throw Form::GradeTooLowException();
}

// ── Copy constructor ──────────────────────────────────────────────────────────
Form::Form(Form const& other)
	: _name(other._name), _isSigned(other._isSigned),
	  _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute)
{}

// ── Copy assignment operator ──────────────────────────────────────────────────
// Const members (_name, _gradeToSign, _gradeToExecute) cannot be reassigned.
// Only _isSigned (the sole mutable attribute) is updated.
Form& Form::operator=(Form const& other)
{
	if (this != &other)
		_isSigned = other._isSigned;
	return *this;
}

// ── Destructor ────────────────────────────────────────────────────────────────
Form::~Form(void)
{}

// ── Getters ───────────────────────────────────────────────────────────────────
std::string const& Form::getName(void) const
{
	return _name;
}

bool Form::getIsSigned(void) const
{
	return _isSigned;
}

int Form::getGradeToSign(void) const
{
	return _gradeToSign;
}

int Form::getGradeToExecute(void) const
{
	return _gradeToExecute;
}

// ── beSigned ──────────────────────────────────────────────────────────────────
// Signs the form if the bureaucrat's grade is high enough (numerically <=).
// Grade 1 is the highest: a bureaucrat of grade 5 can sign a form requiring
// grade 10 (5 <= 10), but not one requiring grade 3 (5 > 3).
void Form::beSigned(Bureaucrat const& b)
{
	if (b.getGrade() > _gradeToSign)
		throw Form::GradeTooLowException();
	_isSigned = true;
}

// ── Exception messages ────────────────────────────────────────────────────────
const char* Form::GradeTooHighException::what(void) const throw()
{
	return "Form grade is too high (minimum grade is 1)";
}

const char* Form::GradeTooLowException::what(void) const throw()
{
	return "Bureaucrat's grade is too low to sign this form";
}

// ── operator<< ────────────────────────────────────────────────────────────────
// Displays the complete state of the Form as required by the eval sheet.
std::ostream& operator<<(std::ostream& os, Form const& f)
{
	os << "Form [" << f.getName() << "]"
	   << " | signed: "          << (f.getIsSigned() ? "yes" : "no")
	   << " | grade to sign: "   << f.getGradeToSign()
	   << " | grade to execute: "<< f.getGradeToExecute();
	return os;
}

