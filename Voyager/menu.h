#ifndef MENU_H
#define MENU_H

#include "game.h"

class Game; // Forward declaration of Game class

/*
All menu does is set up the main menu screen with options for the player to choose from. 
It will also be used to display other information available on the
main menu, such as credits, and instructions.
*/

class Menu {
public:
	void setMenu(Game&) const;
    void setInstructions(Game&) const;
    void setCredits(Game&) const;
    void setError(Game&) const;
    void setIntro(Game&) const;
};

#endif