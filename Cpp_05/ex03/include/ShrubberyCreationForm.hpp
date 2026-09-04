#ifndef SHRUBBERYCREATIONFORM_HPP
# define SHRUBBERYCREATIONFORM_HPP

# include "AForm.hpp"
# include <string>

class ShrubberyCreationForm : public AForm
{
public:
	// ── Orthodox Canonical Form ──────────────────────────────────────────
	ShrubberyCreationForm(void);
	ShrubberyCreationForm(std::string const& target);
	ShrubberyCreationForm(ShrubberyCreationForm const& other);
	ShrubberyCreationForm& operator=(ShrubberyCreationForm const& other);
	virtual ~ShrubberyCreationForm(void);

protected:
	// Only the action — grade/sign checks are done in AForm::execute()
	virtual void	doExecute(Bureaucrat const& executor) const;

private:
	std::string	_target;
};

#endif // SHRUBBERYCREATIONFORM_HPP
