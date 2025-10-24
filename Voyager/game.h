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
    std::string art_output;   // Art output
    std::string body_output;  // Text output
    std::string error_output; // Error output
    int onMenu; // Flag to check if in menu screen
    int onShip; // Flag to check if on the ship
    int onPlanet; // Flag to check if we are on a planet

public:
    Game();                     // Default constructor
    void setBodyOutput(const std::string&);  // Output text setter
    void setArtOutput(const std::string&);   // Art text setter
    void setErrorOutput(const std::string&); // Error text setter
    void setMenuFlag(const int&);
    void setShipFlag(const int&);
    void setPlanetFlag(const int&);
    std::string getBodyOutput() const;      // Output text getter
    std::string getArtOutput() const;       // Art text getter
    std::string getErrorOutput() const;      // Error text getter
    int getMenuFlag() const;
    int getShipFlag() const;
    int getPlanetFlag() const;

    void clearScreen() const;   // Clears the console screen
    void displayOutput() const; // Displays text, art, and input field
    void gameLoop(Game&) const; // Main game loop
};

#endif // GAME_H