#ifndef MENU_H
#define MENU_H

#include <string>
/*
All menu does is set up the main menu screen with options for the player to choose from. 
It will also be used to display other information available on the
main menu, such as credits, and instructions.
*/

class Menu {
public:
	std::string setMenu() const;
    std::string setInstructions() const;
    std::string setCredits() const;
    std::string setError() const;
    std::string setIntro() const;
};

#endif