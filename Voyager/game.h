#ifndef GAME_H
#define GAME_H

#include"command.h"

#include <sstream>
#include <string>
#include <vector>

/*
- Game class to manage game state and interactions
- Game class will take in input for the command as a stringstream to parse the 2-3 words in the command
- Game class should be able to handle regex, and passing commands onto certain outputs
*/
class Game {
private:
    std::string text_output; // Text output
    std::string error_output; // Error output
    std::string art_output; // Art output
public:
    Game();                     // Default constructor
    void displayOutput() const; // Displays text, art, and input field
    void setTextOutput(const std::string&); // Output text setter
    std::string getTextOutput() const;      // Output text getter
    void setArtOutput(const std::string&);  // Art text setter
    std::string getArtOutput() const;       // Art text getter
    void setErrorOutput(const std::string&); // Error text setter
    std::string getErrorOutput() const;      // Error text getter
    void clearScreen() const;
};

#endif // GAME_H