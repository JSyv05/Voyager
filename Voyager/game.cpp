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
void Game::setShipFlag(const bool& flag) { onShip = flag; }
void Game::setPlanetFlag(const bool& flag) { onPlanet = flag; }
void Game::setGameOverFlag(const bool& flag) { gameOver = flag; }
void Game::setNextFlag(const bool& flag) { next = flag; }
string Game::getArtOutput() const { return art_output; }
string Game::getBodyOutput() const { return body_output; }
string Game::getErrorOutput() const { return error_output; }
bool Game::getMenuFlag() const { return onMenu; }
bool Game::getShipFlag() const { return onShip; }
bool Game::getPlanetFlag() const { return onPlanet; }
bool Game::getGameOverFlag() const { return gameOver; }
bool Game::getNextFlag() const { return next; }

/*
Each if and else if statement ub the check functions is checking for the command, 
and returns an enum that matches that command.
*/

Game::MainMenuCommand Game::checkMenuCommand(Command& command) const{
    const auto& input = command.getInput();
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
    const auto& input = command.getInput();
    if (input.empty()) {
        return PlanetCommand::Error;
    }
}

Game::NextCommand Game::checkNextCommand(Command& command) const {
    const auto& input = command.getInput();
    if (input.empty() || (input.size() == 1 && input[0] == "next")) {
        return NextCommand::Next;
    }
    else {
        return NextCommand::Error;
    }
}

/*
This function checks to see what operating system the game is running on, either Windows, or some Unix-based
OS like Linux or MacOS
*/

void Game::clearScreen() const {
#ifdef _WIN32
    // Windows system clear screen command
    system("cls");
#else
    // Unix-based system clear screen command
    system("clear");
#endif
}

/*
This function combines the values for art, body, and error and displays all of that as one thing.
*/

void Game::displayOutput() const {
    string output = getArtOutput() + "\n\n" + getBodyOutput() + "\n\n" +
                    getErrorOutput(); 
    cout << output;                            
}

/*
The game loop is the heart of the game. It will handle all game logic, like checking game states,
checking the commands passed, and running the logic behind each command.
*/

void Game::gameLoop(Game& game) const {
    Menu menu; // Create menu object
    Command command; // Create command object
    game.setMenuFlag(true); // sets menu flag to true

    menu.setMenu(game); // Set main menu

    while (!game.getGameOverFlag()) {

        /*
        Display the main menu initially and then take input. The display will update before the end of each iteration
        */

        game.displayOutput(); 
        command.setInput();
        /*
        Each if and else if statement is checking for game state. If we are on the menu, 
        then it will only check for menu commands, and so on.
        */

        if (game.getMenuFlag()) {

            /*
            This switch case will check each case of the defined enum, MainMenuCommand 
            in this case, and then run the logic of the command based on that case.
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
                game.setGameOverFlag(true);
                break;
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
                game.setNextFlag(false);
                game.setMenuFlag(false);
                game.setShipFlag(true);
                game.setArtOutput("");
                game.setBodyOutput("We should now be on the ship");
                game.setErrorOutput("");
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
