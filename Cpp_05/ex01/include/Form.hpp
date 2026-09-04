#ifndef FORM_HPP
# define FORM_HPP

# include <iostream>
# include <string>
# include <exception>

// Forward declaration to avoid circular include
class Bureaucrat;

class Form
{
public:
	// ── Orthodox Canonical Form ──────────────────────────────────────────
	Form(void);
	Form(std::string const& name, int gradeToSign, int gradeToExecute);
	Form(Form const& other);
	Form& operator=(Form const& other);
	~Form(void);

	// ── Getters ──────────────────────────────────────────────────────────
	std::string const&	getName(void) const;
	bool				getIsSigned(void) const;
	int					getGradeToSign(void) const;
	int					getGradeToExecute(void) const;

	// ── Signing ──────────────────────────────────────────────────────────
	// Signs the form if bureaucrat's grade is high enough (grade <= _gradeToSign).
	// Throws GradeTooLowException otherwise.
	void	beSigned(Bureaucrat const& b);

	// ── Nested exception classes ─────────────────────────────────────────
	class GradeTooHighException : public std::exception
	{
	public:
		virtual const char*	what(void) const throw();
	};

	class GradeTooLowException : public std::exception
	{
	public:
		virtual const char*	what(void) const throw();
	};

private:
	// ALL attributes are private, NOT protected (subject explicit requirement).
	std::string const	_name;
	bool				_isSigned;       // false at construction
	int const			_gradeToSign;    // constant, validated at construction
	int const			_gradeToExecute; // constant, validated at construction
};

std::ostream&	operator<<(std::ostream& os, Form const& f);

#endif // FORM_HPP

