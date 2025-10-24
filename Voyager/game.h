#ifndef GAME_H
#define GAME_H

#include"command.h"
#include"planet.h"
#include"menu.h"

#include <sstream>
#include <string>
#include <vector>

/*
The function of the Game class is to manage the overall state and flow of the game.
It handles all text and art output, manages the game loop, and keeps track
of the game state that we are in (on menu, on ship, on planet, etc.).
*/
class Game {
private:
    std::string text_output; // Text output
    std::string error_output; // Error output
    std::string art_output; // Art output
    int onMenu; // Flag to check if in menu screen
    int onShip; // Flag to check if on the ship
    int onPlanet; // Flag to check if we are on a planet

public:
    Game();                     // Default constructor
    void displayOutput() const; // Displays text, art, and input field
    void setTextOutput(const std::string&); // Output text setter
    std::string getTextOutput() const;      // Output text getter
    void setArtOutput(const std::string&);  // Art text setter
    std::string getArtOutput() const;       // Art text getter
    void setErrorOutput(const std::string&); // Error text setter
    std::string getErrorOutput() const;      // Error text getter
    void clearScreen() const;                // Clears the console screen
    void gameLoop(Command&, Planet&, Menu&) const; // Main game loop
};

#endif // GAME_H