#ifndef PRESIDENTIALPARDONFORM_HPP
# define PRESIDENTIALPARDONFORM_HPP

# include "AForm.hpp"
# include <string>

class PresidentialPardonForm : public AForm
{
public:
	// ── Orthodox Canonical Form ──────────────────────────────────────────
	PresidentialPardonForm(void);
	PresidentialPardonForm(std::string const& target);
	PresidentialPardonForm(PresidentialPardonForm const& other);
	PresidentialPardonForm& operator=(PresidentialPardonForm const& other);
	virtual ~PresidentialPardonForm(void);

protected:
	virtual void	doExecute(Bureaucrat const& executor) const;

private:
	std::string	_target;
};

#endif // PRESIDENTIALPARDONFORM_HPP
