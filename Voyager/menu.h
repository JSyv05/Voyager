#ifndef MENU_H
#define MENU_H

#include "command.h"
#include "game.h"

class Menu {
public:
    Menu();
    void setMainMenu(Game&) const;
    void MainMenu(Command, Game) const;
};

#endif
