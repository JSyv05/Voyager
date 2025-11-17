#ifndef HELP_H
#define HELP_H

#include <string>

class Help {
public:
    std::string getScanHelp() const;
    std::string getTravelHelp() const;
    std::string getGeneralHelp() const;
};

#endif
