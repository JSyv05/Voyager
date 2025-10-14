#ifndef GAME_H
#define GAME_H
#include <sstream>
#include <string>
#include <regex>
#include <vector>

using namespace std;
/*
- Game class to manage game state and interactions
- Game class will take in input for the command as a stringstream to parse the 2-3 words in the command
- Game class should be able to handle regex, and passing commands onto certain outputs
*/
class Game {
private:
    string text_output; // Text output
    string error_output; // Error output
    string art_output; // Art output
    string input; // Command input
    string clear_screen; // Clear screen string using ANSI escape characters
    vector<string> tokens; // Tokenized version of our command input
    regex regexv; // Regex to search for verbs
    regex regexn; // Regex to search for nouns

public:
    Game();
    void displayOutput() const; // Displays text, art, and input field
    void setTextOutput(const string& text); // Output text setter
    string getTextOutput() const; // Output text getter
    void setArtOutput(const string& art); // Art text setter
    string getArtOutput() const; // Art text getter
    void setErrorOutput(const string& error); // Error text setter
    string getErrorOutput() const; // Error text getter
    void clearScreen() const;
    void setInput();
    vector<string> *getInput();
    void mainMenuLoop();
    void mainMenu(); // Displays the default main menu
};

#endif // GAME_H