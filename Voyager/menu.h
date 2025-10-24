#ifndef MENU_H
#define MENU_H

#include "command.h"
#include "game.h"

class Game; // Forward declaration of Game class

class Menu {
public:
	void setMenu(Game& g);
};

#endif