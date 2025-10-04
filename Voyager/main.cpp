// Standard C++ libraries
#include <iostream>
#include <sstream>
#include <string>
#include <regex>
#include <vector>

// User created libraries
#include "game.h"

int main() {
    Game game; // Create game object

    game.mainMenu(); // Load initial main menu
    game.displayOutput(); // Displays the initial output
    game.getInput(); // provides input field
	std::cout << "Hello, Voyager!" << std::endl;
	return 0;
}


// Function implementation for Game class

Game::Game() : text_output(""), art_output("") {} // Default constructor for game class

void Game::setTextOutput(const std::string& text) {
    text_output = text; // Set text output
} 

std::string Game::getTextOutput() const {
	return text_output; // Get text output
}

std::string Game::getArtOutput() const {
	return art_output; // Get art output
}

void Game::setArtOutput(const std::string& art) {
    art_output = art; // Set art output
} 

void Game::displayOutput() const {
	std::string output = Game::getArtOutput() + "\n\n" + Game::getTextOutput(); // Combine text and art output
	std::cout << output; // Display combined output
}

void Game::getInput() {
    tokens.clear(); // Empties command vector of previous commands

    std::cout << "> "; // Input field
    std::getline(std::cin, input); // Take in input from entire line

    std::stringstream untokenizedInput(input); // Convert the input to a stringstream to tokenize input
    std::string token; // Temp variable that will store the individual tokens of the input

    while (untokenizedInput >> token) { // While loop that pushes each token to the end of the list
        tokens.push_back(token); // Appends the token to the end of the list, tokens[0] contains the command and tokens[1] contains the argument. If the is a predicate, token[2] will contain the argument
    }

    std::cout << "Command: " << tokens[0] << std::endl << "Argument: " << tokens[1] << std::endl; // Test to see if parsing was successful
}

void Game::mainMenu(){
    art_output = R"(
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

    text_output = "1. Start Game\n"
                  "2. Load Game\n"
                  "3. Instructions\n"
                  "4. Credits\n"
                  "5. Exit\n\n"
                  "Please enter your choice\n\n"; // Main menu text
}