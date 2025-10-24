#ifndef MENU_H
#define MENU_H

#include "command.h"
#include "game.h"

class Game; // Forward declaration of Game class

/*
All menu does is set up the main menu screen with options for the player to choose from. 
It will also be used to display other information available on the
main menu, such as credits, and instructions.
*/

class Menu {
public:
	void setMenu(Game& g) const;
    void setInstructions(Game& g) const;
    void setCredits(Game& g) const;
};

#endif