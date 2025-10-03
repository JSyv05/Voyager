#ifndef GAME_H
#define GAME_H
#include <string>
/*
Game class to manage game state and interactions
*/
class Game {
private:
    std::string text_output;
    std::string art_output;
    std::string output;

public:
    Game();
    void displayOutput() const;
    void setTextOutput(const std::string& text);
    std::string getTextOutput() const;
    std::string getArtOutput() const;
    void setArtOutput(const std::string& art);
    void clearOutputs();
    void getInput();
    void mainMenu();
    void startGame();
};

#endif // GAME_H