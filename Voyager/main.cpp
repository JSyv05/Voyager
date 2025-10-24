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
#include "game.h"
using namespace std;

int main() {
    Game game;

	game.gameLoop(game);

	return 0;
}

