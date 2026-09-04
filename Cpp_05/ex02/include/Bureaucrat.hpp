#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

# include <iostream>
# include <string>
# include <exception>

class AForm;

class Bureaucrat
{
public:
	// ── Orthodox Canonical Form ──────────────────────────────────────────
	Bureaucrat(void);
	Bureaucrat(std::string const& name, int grade);
	Bureaucrat(Bureaucrat const& other);
	Bureaucrat& operator=(Bureaucrat const& other);
	~Bureaucrat(void);

	// ── Getters ──────────────────────────────────────────────────────────
	std::string const&	getName(void) const;
	int					getGrade(void) const;

	// ── Grade manipulation ───────────────────────────────────────────────
	void	incrementGrade(void);
	void	decrementGrade(void);

	// ── Form interaction ─────────────────────────────────────────────────
	void	signForm(AForm& form);
	void	executeForm(AForm const& form);

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
	std::string const	_name;
	int					_grade;
};

std::ostream&	operator<<(std::ostream& os, Bureaucrat const& b);

#endif // BUREAUCRAT_HPP

