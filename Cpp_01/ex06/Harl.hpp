#ifndef HARL_FILTER_HPP
#define HARL_FILTER_HPP

#include <string>

class Harl {
public:
    Harl();
    void complain(std::string level);
    void complainFrom(int level);
private:
    void debug(void);
    void info(void);
    void warning(void);
    void error(void);
};

#endif
