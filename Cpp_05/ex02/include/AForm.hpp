#ifndef AFORM_HPP
# define AFORM_HPP

# include <iostream>
# include <string>
# include <exception>

class Bureaucrat;

class AForm
{
public:
	// ── Orthodox Canonical Form ──────────────────────────────────────────
	AForm(void);
	AForm(std::string const& name, int gradeToSign, int gradeToExecute);
	AForm(AForm const& other);
	AForm& operator=(AForm const& other);
	virtual ~AForm(void); // virtual: safe deletion through base pointer

	// ── Getters ──────────────────────────────────────────────────────────
	std::string const&	getName(void) const;
	bool				getIsSigned(void) const;
	int					getGradeToSign(void) const;
	int					getGradeToExecute(void) const;

	// ── Signing ──────────────────────────────────────────────────────────
	void	beSigned(Bureaucrat const& b);

	// ── Execution ────────────────────────────────────────────────────────
	// Concrete: performs isSigned + grade checks, then delegates to doExecute().
	// Making AForm abstract via the pure doExecute() below is the elegant
	// approach hinted at by the subject ("one way is more elegant than the other").
	void				execute(Bureaucrat const& executor) const;

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

	class FormNotSignedException : public std::exception
	{
	public:
		virtual const char*	what(void) const throw();
	};

	class GradeTooLowToExecuteException : public std::exception
	{
	public:
		virtual const char*	what(void) const throw();
	};

protected:
	// Pure virtual: subclasses implement ONLY the action (no grade checks needed).
	// This is what makes AForm abstract.
	virtual void	doExecute(Bureaucrat const& executor) const = 0;

private:
	// ALL private — subclasses access via public getters.
	std::string const	_name;
	bool				_isSigned;
	int const			_gradeToSign;
	int const			_gradeToExecute;
};

std::ostream&	operator<<(std::ostream& os, AForm const& f);

#endif // AFORM_HPP

