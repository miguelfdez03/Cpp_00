#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <iostream>
#include <string>

class Zombie {
public:
    Zombie();
    Zombie(std::string name);
    ~Zombie();

    void announce(void) const;
    void setName(std::string const &name);
    std::string const &getName() const;

private:
    std::string name;
};

#endif // ZOMBIE_HPP
