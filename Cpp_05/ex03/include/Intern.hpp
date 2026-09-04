#ifndef INTERN_HPP
# define INTERN_HPP

# include <string>
# include "AForm.hpp"

class Intern
{
public:
	// ── Orthodox Canonical Form ──────────────────────────────────────────
	// The Intern has no name, no grade, no unique state — all instances are
	// interchangeable. OCF is still required by the eval sheet.
	Intern(void);
	Intern(Intern const& other);
	Intern& operator=(Intern const& other);
	~Intern(void);

	// ── Factory method ───────────────────────────────────────────────────
	// Returns a heap-allocated AForm* of the type named by 'formName',
	// targeted at 'target'. Caller is responsible for delete.
	// Prints "Intern creates <form>" on success.
	// Prints an error message if formName is unknown.
	AForm*	makeForm(std::string const& formName, std::string const& target) const;
};

#endif // INTERN_HPP

