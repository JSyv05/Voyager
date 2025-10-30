// User created libraries
#include "command.h"
#include "menu.h"
#include "ship.h"
#include "planet.h"
#include "game.h"

// Standard C++ libraries
#include <iostream>

using namespace std;
            
// Function implementation for Game class

Game::Game(): 
    art_output(""), 
    body_output(""), 
    error_output(""), 
    onMenu(false), 
    onShip(false), 
    onPlanet(false),
    gameOver(false), 
    saved(false),
    next(false) {}

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
void Game::setSavedFlag(const bool& flag) { saved = flag; }

string Game::getArtOutput() const { return art_output; }
string Game::getBodyOutput() const { return body_output; }
string Game::getErrorOutput() const { return error_output; }

bool Game::getMenuFlag() const { return onMenu; }
bool Game::getShipFlag() const { return onShip; }
bool Game::getPlanetFlag() const { return onPlanet; }
bool Game::getGameOverFlag() const { return gameOver; }
bool Game::getNextFlag() const { return next; }
bool Game::getSavedFlag() const { return saved; }

/*
Each if statement checks the command size, command content, and 
then the game state, and will return the corresponding command.
These will be used in the game loop to manage core logic behind
commands
*/

Game::ValidCommand Game::checkCommand(const Command& command,const Game& game) const {
    const auto& input = command.getInput();
    if (input.empty() && !game.getNextFlag()) {
        return ValidCommand::Error;
    }
    else if (input.size() >= 1 && input[0] == "collect" && game.getPlanetFlag()) {
        return ValidCommand::Collect;
    }
    else if (input.size() == 1 && input[0] == "credits" && game.getMenuFlag()) {
        return ValidCommand::Credits;
    }
    else if (input.size() >= 1 && input[0] == "drop" && game.getPlanetFlag()) {
        return ValidCommand::Drop;
    }
    else if (input.size() == 1 && input[0] == "exit" && game.getMenuFlag()) {
        return ValidCommand::Exit;
    }
    else if (input.size() == 1 && input[0] == "instructions" && game.getMenuFlag()) {
        return ValidCommand::Instructions;
    }
    else if (((input.size() == 1 && input[0] == "back") ||
              (input.size() == 1 && input[0] == "menu") ||
              (input.size() >= 2 && input[0] == "main" && input[1] == "menu")) && game.getMenuFlag()) {
        return ValidCommand::MainMenu;
    }
    else if (((input.size() == 1 && input[0] == "load") ||
             (input.size() >= 2 && input[0] == "load" && input[1] == "game")) && game.getMenuFlag()) {
        return ValidCommand::Load;
    }
    else if ((input.empty() || (input.size() == 1 && input[0] == "next")) && game.getNextFlag()) {
        return ValidCommand::Next;
    }
    else if ((input.size() >= 3 && input[0] == "return" && input[1] == "to" && input[3] == "ship") && game.getPlanetFlag()) {
        return ValidCommand::ReturnToShip;
    }
    else if ((input.size() == 1 && input[0] == "save") || 
             (input.size() >= 2 && input[0] == "save" && input[1] == "game") && !game.getMenuFlag()) {
        return ValidCommand::Save;
    }
    else if (input.size() == 1 && input[0] == "scan" && game.getPlanetFlag()) {
        return ValidCommand::Scan;
    }
    else if (input.size() == 1 && input[0] == "exit" && game.getShipFlag() && game.getSavedFlag()) {
        return ValidCommand::ShipExit;
    }
    else if (((input.size() == 1 && input[0] == "menu") ||
              (input.size() >= 2 && input[0] == "main" && input[1] == "menu")) && game.getMenuFlag() && game.getSavedFlag()) {
        return ValidCommand::ShipMainMenu;
    }
    else if (input.size() == 1 && input[0] == "scan" && game.getShipFlag()) {
        return ValidCommand::ScanForPlanets; 
    }
    else if (((input.size() == 1 && input[0] == "start") ||
        (input.size() >= 2 && input[0] == "start" && input[1] == "game")) && game.getMenuFlag()) {
        return ValidCommand::Start;
    }
    else if (input.size() >= 3 && input[0] == "travel" && input[1] == "to" && game.getShipFlag()) {
        return ValidCommand::Travel;
    }
    else {
        return ValidCommand::Error;
    }
}

/*
This function checks to see what operating system the game is running on, either Windows, or some 
Unix-based OS like Linux or MacOS. It will then run the corresponding command to clear the terminal.
A clean and easy way to implement cross compatibility into our game
*/

void Game::clearScreen() const {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/*
This function combines the values for art, body, and error and displays all of that as one output.
*/

void Game::displayOutput() const {
    string output = getArtOutput() + "\n\n" + getBodyOutput() + "\n\n" +
                    getErrorOutput(); 
    cout << output;                            
}

void Game::saveGame() {}

/*
The game loop is the heart of the game. It will handle all of the displaying of outputs as well as the logic behind each command.
*/

void Game::gameLoop(Game& game) const {
    // initializations for initial game objects
    Menu menu;
    Command command;
    Ship ship;

    string error; // string to store error messages

    game.setMenuFlag(true);
    menu.setMenu(game);

    while (!game.getGameOverFlag()) {

        /*
        Display the main menu initially and then take input.
        Contents of the display will be updated in the switch case
        */

        game.displayOutput(); 
        command.setInput();

        /*
        This is where all of the command logic will be stored. It will go over each
        enum value in ValidCommand and run the corresponding logic behind each command
        */

        ValidCommand passedCommand = game.checkCommand(command, game);
        switch (passedCommand) {
        case ValidCommand::Collect:
            break;
        case ValidCommand::Credits:
            menu.setCredits(game);
            break;
        case ValidCommand::Drop:
            break;
        case ValidCommand::Error:
            error = "ERR: Please enter a valid input\n\n";
            game.setErrorOutput(error);
            break;
        case ValidCommand::Exit:
            game.setGameOverFlag(true);
            break;
        case ValidCommand::Instructions:
            menu.setInstructions(game);
            break;
        case ValidCommand::Load:
            break;
        case ValidCommand::MainMenu:
            menu.setMenu(game);
            break;
        case ValidCommand::Next:
            game.setNextFlag(false);
            game.setMenuFlag(false);
            game.setShipFlag(true);
            game.setBodyOutput("We should now be in the game");
            break;
        case ValidCommand::ReturnToShip:
            game.setPlanetFlag(false);
            game.setShipFlag(true);
            break;
        case ValidCommand::Save:
            game.saveGame();
            break;
        case ValidCommand::Scan:
            break;
        case ValidCommand::ShipExit:
            game.setGameOverFlag(true);
            break;
        case ValidCommand::ShipMainMenu:
            menu.setMenu(game);
            game.setMenuFlag(true);
            game.setShipFlag(false);
            break;
        case ValidCommand::ScanForPlanets:

            break;
        case ValidCommand::Start:
            game.setMenuFlag(false);
            game.setNextFlag(true);
            menu.setIntro(game);
            break;
        case ValidCommand::Travel:
            game.setPlanetFlag(true);
            game.setShipFlag(false);
            break;
        default:
            error = "ERR: PLease enter a valid input\n\n";
            game.setErrorOutput(error);
            break;
        }
        game.clearScreen(); // Clear screen before start of next loop iteration
    }

}
