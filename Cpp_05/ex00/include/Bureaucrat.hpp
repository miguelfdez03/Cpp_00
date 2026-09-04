#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

# include <iostream>
# include <string>
# include <exception>

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
	// incrementGrade: moves grade toward 1 (highest). grade 3 → grade 2.
	void	incrementGrade(void);
	// decrementGrade: moves grade toward 150 (lowest). grade 3 → grade 4.
	void	decrementGrade(void);

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
	std::string const	_name;   // constant: never changes after construction
	int					_grade;  // valid range: [1, 150]
};

// ── Non-member operator overload ─────────────────────────────────────────────
std::ostream&	operator<<(std::ostream& os, Bureaucrat const& b);

#endif // BUREAUCRAT_HPP

