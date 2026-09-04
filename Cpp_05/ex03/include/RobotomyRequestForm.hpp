#ifndef ROBOTOMYREQUESTFORM_HPP
# define ROBOTOMYREQUESTFORM_HPP

# include "AForm.hpp"
# include <string>

class RobotomyRequestForm : public AForm
{
public:
	// ── Orthodox Canonical Form ──────────────────────────────────────────
	RobotomyRequestForm(void);
	RobotomyRequestForm(std::string const& target);
	RobotomyRequestForm(RobotomyRequestForm const& other);
	RobotomyRequestForm& operator=(RobotomyRequestForm const& other);
	virtual ~RobotomyRequestForm(void);

protected:
	virtual void	doExecute(Bureaucrat const& executor) const;

private:
	std::string	_target;
};

#endif // ROBOTOMYREQUESTFORM_HPP
