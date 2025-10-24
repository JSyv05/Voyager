// User created libraries
#include "command.h"
#include "menu.h"
#include "planet.h"
#include "game.h"

// Standard C++ libraries
#include <iostream>

using namespace std;
            
// Function implementation for Game class

Game::Game()
    : art_output(""), body_output(""), error_output(""), onMenu(0), onShip(0), onPlanet(0) {
} // Default constructor for game class

void Game::setBodyOutput(const string& text) { body_output = text; }
void Game::setArtOutput(const string& art) { art_output = art; }
void Game::setErrorOutput(const string& error) { error_output = error; }
void Game::setMenuFlag(const int& i) { onMenu = i; }
void Game::setShipFlag(const int& i) { onMenu = i; }
void Game::setPlanetFlag(const int& i) { onMenu = i; }
string Game::getBodyOutput() const { return body_output; }
string Game::getArtOutput() const { return art_output; }
string Game::getErrorOutput() const { return error_output; }
int Game::getMenuFlag() const { return onMenu; }
int Game::getShipFlag() const { return onMenu; }
int Game::getPlanetFlag() const { return onMenu; }

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
                    getErrorOutput() + "\n\n"; // Combine text and art output
    cout << output;                            // Display combined output
}

void Game::gameLoop(Game& game) const {
    int run = 1; // Flag to control game loop
    Menu menu; // Create menu object
    Command command; // Create command object
    int menuFlag = 1; // Initial menu flag to start with menu commands
    game.setMenuFlag(menuFlag); // sets menu flag to menuFlag

    menu.setMenu(game); // Set main menu

    while (run) {
        game.displayOutput(); // Display output
        command.setInput(); // set input

        if (game.getMenuFlag()) {
            cout << "In menu\n";
        }
        game.clearScreen(); // Clear screen before start of next loop iteration
    }

}
