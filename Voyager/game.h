#ifndef GAME_H
#define GAME_H
#include <sstream>
#include <string>
#include <regex>
#include <vector>
/*
- Game class to manage game state and interactions
- Game class will take in input for the command as a stringstream to parse the 2-3 words in the command
- Game class should be able to handle regex, and passing commands onto certain outputs
*/
class Game {
private:
    std::string text_output; // Text output
    std::string art_output; // Art output
    std::string input; // Command input
    std::vector<std::string> tokens; // Tokenized version of our command input
    std::regex regexv; // Regex to search for verbs
    std::regex regexn; // Regex to search for nouns

public:
    Game();
    void displayOutput() const; // Displays text, art, and input field
    void setTextOutput(const std::string& text); // Output text setter
    std::string getTextOutput() const; // Output text getter
    void setArtOutput(const std::string& art); // Art text setter
    std::string getArtOutput() const; // Art text getter
    void clearOutputs();
    void getInput();
    void mainMenu(); // Displays the default main menu
    void startGame();
};

#endif // GAME_H