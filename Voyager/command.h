#ifndef COMMAND_H
#define COMMAND_H

#include<string>
#include<vector>

class Command {
public:
    std::string input;
    std::vector<std::string> command;
    void setInput();
    std::vector<std::string>* getInput();
};

#endif