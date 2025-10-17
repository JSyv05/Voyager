// User created libraries
#include "command.h"
#include "game.h"

// Standard C++ libraries
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
            
// Function implementation for Game class

Game::Game()
    : text_output(""), error_output(""), art_output("") {
} // Default constructor for game class

string Game::getTextOutput() const {
    return text_output; // Get text output
}

void Game::setTextOutput(const string& text) {
    text_output = text; // Set text output
}

string Game::getArtOutput() const {
    return art_output; // Get art output
}

void Game::setArtOutput(const string& art) {
    art_output = art; // Set art output
}

string Game::getErrorOutput() const {
    return error_output; // Get error output
}

void Game::setErrorOutput(const string& error) {
    error_output = error; // Set error output
}

void Game::displayOutput() const {
    string output = getArtOutput() + "\n\n" + getTextOutput() + "\n\n" +
                    getErrorOutput() + "\n\n"; // Combine text and art output
    cout << output;                            // Display combined output
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
