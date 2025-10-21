// Standard C++ libraries
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <regex>
#include <vector>

// User created libraries
#include "command.h"
#include "game.h"
#include "menu.h"
#include "planet.h"

using namespace std;

int main() {
    Command command; // Create command object]
    Game game; // Create game object
    Menu menu;       // Create menu object

    menu.MainMenu(command, game); // Display main menu loop
    game.clearScreen();

	cout << "Hello, Voyager!" << endl;
	return 0;
}

// end 
