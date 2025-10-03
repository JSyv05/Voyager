// Standard C++ libraries
#include <iostream>
#include <sstream>
#include <string>
#include <regex>

// User created libraries
#include "game.h"

int main() {
    Game game; // Create game object

    game.mainMenu(); // Load initial main menu
    game.displayOutput(); // Displays the initial output
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
                  "Please enter your choice\n\n"
                  "> "; // Main menu text
}