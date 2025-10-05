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
    game.getInput(); // Provides input field
    game.clearScreen(); // Clear the screen
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

void Game::clearScreen() {
    std::cout << "\033[2J\033[1;1H"; 
    
    /*
    - This code uses an ANSI escape code, a highly extensible feature that can allow you to format text
    format for ansi escape characters: <escape-character>[<parameter><command>
    - \033 represents the escape character. \x1b and \e are also viable options for their own reasons
    - in this case there are two ANSI escape codes being used
    - \033 initializes the escape character, [ is the Control Sequence Intoducer and allows us to pass certain parameters
    - J is the command to erase in display, 2 is the parameter that erases the entire screen. 1 would erase everything behind the cursor
    - The same logic applies to the second ANSI escape character \033[1;1H
    - H is the command for the cursor
    - 1;1 is the position the cursor will return to, in this case, the beginning of the file
    */
}

void Game::getInput() {
    tokens.clear(); // Empties command vector of previous commands

    std::cout << "> "; // Input field
    std::getline(std::cin, input); // Take in input from entire line

    std::stringstream untokenizedInput(input); // Convert the input to a stringstream to tokenize input
    std::string token; // Temp variable that will store the individual tokens of the input

    while (untokenizedInput >> token) { // While loop that pushes each token to the end of the list
        tokens.push_back(token); // Appends the token to the end of the list tokens, tokens[0] contains the command and tokens[1] contains the argument. If the is a predicate, token[2] will contain the argument
    }
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