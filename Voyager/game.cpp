// User created libraries
#include "command.h"
#include "menu.h"
//#include "planet.h"
#include "game.h"

// Standard C++ libraries
#include <iostream>
#include <vector>

using namespace std;
            
// Function implementation for Game class

Game::Game(): 
    art_output(""), 
    body_output(""), 
    error_output(""), 
    onMenu(false), 
    onShip(false), 
    onPlanet(false),
    next(false),
    gameOver(false) {} // Default constructor for game class

/*
Setters and getters for all outputs and game state flags
*/

void Game::setArtOutput(const string& art) { art_output = art; }
void Game::setBodyOutput(const string& body) { body_output = body; }
void Game::setErrorOutput(const string& error) { error_output = error; }
void Game::setMenuFlag(const bool& flag) { onMenu = flag; }
void Game::setShipFlag(const bool& flag) { onMenu = flag; }
void Game::setPlanetFlag(const bool& flag) { onMenu = flag; }
void Game::setGameOverFlag(const bool& flag) { gameOver = flag; }
void Game::setNextFlag(const bool& flag) { next = flag; }
string Game::getArtOutput() const { return art_output; }
string Game::getBodyOutput() const { return body_output; }
string Game::getErrorOutput() const { return error_output; }
bool Game::getMenuFlag() const { return onMenu; }
bool Game::getShipFlag() const { return onMenu; }
bool Game::getPlanetFlag() const { return onMenu; }
bool Game::getGameOverFlag() const { return gameOver; }
bool Game::getNextFlag() const { return next; }

Game::MainMenuCommand Game::checkMenuCommand(Command& command) const{
    const auto& input = *command.getInput();
    if (input.empty()) {
        return MainMenuCommand::Error;
    }
    else if ((input.size() == 1 && input[0] == "start") ||
             (input.size() >= 2 && input[0] == "start" && input[1] == "game")) {
        return MainMenuCommand::Start;
    }
    else if ((input.size() == 1 && input[0] == "load") ||
             (input.size() >= 2 && input[0] == "load" && input[1] == "game")) {
        return MainMenuCommand::Load;
    }
    else if (input.size() == 1 && input[0] == "instructions") {
        return MainMenuCommand::Instructions;
    }
    else if (input.size() == 1 && input[0] == "credits") {
        return MainMenuCommand::Credits;
    }
    else if (input.size() == 1 && input[0] == "exit") {
        return MainMenuCommand::Exit;
    }
    else if (input.size() == 1 && input[0] == "back") {
        return MainMenuCommand::Back;
    }
    else {
        return MainMenuCommand::Error;
    }
}

Game::PlanetCommand Game::checkPlanetCommand(Command& command) const {
    const auto& input = *command.getInput();
    if (input.empty()) {
        return PlanetCommand::Error;
    }
}

Game::NextCommand Game::checkNextCommand(Command& command) const {
    const auto& input = *command.getInput();
    if (input.empty() || (input.size() == 1 && input[0] == "next")) {
        return NextCommand::Next;
    }
    else {
        return NextCommand::Error;
    }
}

void Game::clearScreen() const {
#ifdef _WIN32
    // Windows system clear screen command
    system("cls");
#else
    // Unix-based system clear screen command
    system("clear");
#endif
}

void Game::displayOutput() const {
    string output = getArtOutput() + "\n\n" + getBodyOutput() + "\n\n" +
                    getErrorOutput(); // Combine text and art output
    cout << output;                            // Display combined output
}

void Game::gameLoop(Game& game) const {
    Menu menu; // Create menu object
    Command command; // Create command object
    int menuFlag = true; // Initial menu flag to start with menu commands
    game.setMenuFlag(menuFlag); // sets menu flag to menuFlag

    menu.setMenu(game); // Set main menu

    while (!game.getGameOverFlag()) { // Checks to see if game is not over

        game.displayOutput(); // Display output
        command.setInput(); // set input

        if (game.getMenuFlag()) {

            /*
            This if statement will work only when we are on the menu.
            Commands that are only supposed to run on the main menu go into here.
            There is a variable passedCommand that will store the result of our checkMenuCommand.
            Each state defined in the enum will be compared against the result of the command.
            If statements control what is going to happen based on that
            */

            MainMenuCommand passedCommand = game.checkMenuCommand(command); // enum state based on input

            switch (passedCommand) {
            case MainMenuCommand::Start:
                game.setMenuFlag(false);
                game.setNextFlag(true);
                menu.setIntro(game);
                break;
            case MainMenuCommand::Load:
                break;
            case MainMenuCommand::Instructions:
                menu.setInstructions(game);
                break;
            case MainMenuCommand::Credits:
                menu.setCredits(game);
                break;
            case MainMenuCommand::Back:
                menu.setMenu(game);
                break;
            case MainMenuCommand::Exit:
                game.clearScreen();
                exit(0);
            case MainMenuCommand::Error:
                menu.setError(game);
                break;
            default:
                menu.setError(game);
                break;
            }
        }

        else if (game.getPlanetFlag()) {

        }

        else if (game.getShipFlag()) {

        }

        else if (game.getNextFlag()) {
            NextCommand passedCommand = game.checkNextCommand(command);
            switch (passedCommand) {
            case NextCommand::Next:
                game.setShipFlag(true);
                break;
            case NextCommand::Error:
                game.setErrorOutput("ERR: please input a valid command\n\n");
                break;
            default:
                game.setErrorOutput("ERR: please input a valid command\n\n");
                break;
            }
        }

        game.clearScreen(); // Clear screen before start of next loop iteration
    }

}
