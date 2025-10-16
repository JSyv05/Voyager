// Standard C++ libraries
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <regex>
#include <vector>

// User created libraries
#include "game.h"

using namespace std;

int main() {
    Game game; // Create game object

    game.mainMenuLoop();
    game.clearScreen();
	cout << "Hello, Voyager!" << endl;
	return 0;
}


// Function implementation for Game class

Game::Game()
    : text_output(""), error_output(""), art_output(""), start_game(false) {
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
    string output = getArtOutput() + "\n\n" + getTextOutput() + "\n\n" + getErrorOutput() + "\n\n"; // Combine text and art output
    cout << output; // Display combined output
}

void Game::clearScreen() const{
#ifdef _WIN32
    // Windows system clear screen command
    std::system("cls");
#else
    // Unix-based system clear screen command
    std::system("clear");
#endif
}

void Game::setInput() {
    tokens.clear(); // Empties command vector of previous commands

    cout << "> "; // Input field
    getline(cin, input); // Take in input from entire line

    stringstream untokenizedInput(input); // Convert the input to a stringstream to tokenize input
    string token; // Temp variable that will store the individual tokens of the input

    while (untokenizedInput >> token) { // While loop that pushes each token to the end of the list

        transform(token.begin(), token.end(), token.begin(), [](unsigned char c) { return tolower(c); });      // Transforms the token to lowercase
        tokens.push_back(token); // Appends a the lowercased token to the end of the list tokens for the command parser to read.
    }
}

vector<string>* Game::getInput() { return &tokens; } // Returns a pointer to the vector of tokens, which will be used to select individual tokens


void Game::mainMenu(){
    string art = R"(
                :::     ::: :::::::: :::   :::  :::     :::::::: :::::::::::::::::::             
               :+:     :+::+:    :+::+:   :+::+: :+:  :+:    :+::+:       :+:    :+:              
              +:+     +:++:+    +:+ +:+ +:++:+   +:+ +:+       +:+       +:+    +:+               
             +#+     +:++#+    +:+  +#++:+#++:++#++::#:       +#++:++#  +#++:++#:                 
             +#+   +#+ +#+    +#+   +#+ +#+     +#++#+   +#+#+#+       +#+    +#+                 
             #+#+#+#  #+#    #+#   #+# #+#     #+##+#    #+##+#       #+#    #+#                  
              ###     ########    ### ###     ### ######## #############    ###                   
____ _  _ ____ ____ _   _ ____ ____ ____ ____ _ ____ _ ____ ____ _  _ ____ ___ ___ ____ ____ ____ 
|___ |  | |___ |__/  \_/  [__  |__| |    |__/ | |___ | |    |___ |\/| |__|  |   |  |___ |__/ [__  
|___  \/  |___ |  \   |   ___] |  | |___ |  \ | |    | |___ |___ |  | |  |  |   |  |___ |  \ ___] )";  //ASCII art title screen ooooooo

    string err = ""; // Clear error output

    string text = "1. Start Game\n"
                  "2. Load Game\n"
                  "3. Instructions\n"
                  "4. Credits\n"
                  "5. Exit\n\n"
                  "Please enter your choice."; // Main menu text

    setArtOutput(art); // Sets art to title screen
    setErrorOutput(err); // Clears error output
    setTextOutput(text); // Sets text to menu options
}

void Game::mainMenuLoop() {

    /*
    This is the command parser For the main menu. 
    It will take the tokenized command and then check each of the indices for keywords to run commands.
    There should be a command parser for each setting in the game, such as on planets, on the ship, in space, etc. 
    The command parser will be a while loop
    that will continue until the user exits the given area. 
    The command parser will also be able to handle invalid commands and return an error message.
    Each if statement will check each index of the tokenized command for
    keywords. Most of the time, the first index will be the command, and any following indices will be arguments.
    */

    start_game =
        false; // Reset start_game to false whenever we enter the main menu loop

    mainMenu(); // Display main menu
    while (!start_game) {
        clearScreen();
        displayOutput(); // Display output
        setInput();      // Set input
        if (getInput() -> empty()) { // If no input is given
            string err = "ERR) Invalid input. Please enter a valid command."; // returns an error message
            setErrorOutput(err);
        }
        else if ((*getInput())[0] == "start" && (*getInput())[1] == "game") {
            start_game = true;
            string text =
                "This will begin a game. Type back to go back to the main "
                "menu."; // will begin the game. To be implemented later
            setTextOutput(text);

            string err = ""; // Clear error output
            setErrorOutput(err);
        }
        else if ((*getInput())[0] == "load" && (*getInput())[1] == "game") {
            start_game = true;
            string text =
                "This will begin a save game. Type back to go back to the main "
                "menu."; // will load a save game. To be implemented later
            setTextOutput(text);

            string err = ""; // Clear error output
            setErrorOutput(err);
        }
        else if ((*getInput())[0] == "instructions") {
            string text =
                "the goal of Voyageer is to collect as many samples as possible,\n"
                "explore as many planets as possible, and then return to Earth safely.\n"
                "You will be able to use commands to navigate around the solar system \n"
                "simply by typing in a 2-4 word command.\n"
                "(\"Examine Granite\", \"Trade meat with merchat\", etc.)\n\n"
                "The challenge is resource management. You will have to spend samples\n"
                "to maintain the health of your ship and yourself. You will also\n"
                "lose resources from random events that will occur.You will have to make\n"
                "strategic decisions on what to spend resources on as well as what items\n"
                "you need to survive.\n\n"
                "When it comes to space exploration, there is only one saying: \"Every Sacrifice Matters\"\n\n"
                "Type back to return to main menu"; // Instructions and game overview
            setTextOutput(text);

            string err = ""; // Clear error output
            setErrorOutput(err);
        }
        else if ((*getInput())[0] == "credits") {
            string text =
                "Team Members:\nAlina Betances\nAnthony Pinto\nElias Reeves\nMatthew Silva\nJohn Syvertsen\n\n"
                "Scrum Master:\nJohn Syvertsen\n\n"
                "Programmers:\nAlina Betances\nAnthony Pinto\nElias Reeves\nMatthew Silve\nJohn Syvertsen\n\n"
                "Type back to return to the main menu."; // will show credits. To be
                                          // implemented later
            setTextOutput(text);

            string err = ""; // Clear error output
            setErrorOutput(err);
        }
        else if ((*getInput())[0] == "exit") {
            clearScreen();
            exit(0); // Exit the game
        }
        else if ((*getInput())[0] == "back") {
            mainMenu(); // Go back to main menu
        }
        else {
            string err =
                "ERR) Invalid input. Please enter a valid command."; // returns an error message
            setErrorOutput(err);
        }
    }
}