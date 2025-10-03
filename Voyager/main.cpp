#include <iostream>
#include "game.h"
#include <string>
using namespace std;

int main() {
    Game game; // Create game object

    game.mainMenu(); // Load initial main menu
	cout << "Hello, Voyager!" << endl;
	return 0;
}

// Function implementation for Game class

Game::Game() : text_output(""), art_output(""), output("") {} // Default constructor for game class

void Game::setTextOutput(const string& text) {
    text_output = text; // Set text output
} 

string Game::getTextOutput() const {
	return text_output; // Get text output
}

string Game::getArtOutput() const {
	return art_output; // Get art output
}

void Game::setArtOutput(const string& art) {
    art_output = art; // Set art output
} 

void Game::displayOutput() const {
	string output = Game::getArtOutput() + "\n" + Game::getTextOutput() + "\n"; // Combine text and art output
	cout << output; // Display combined output
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
|___  \/  |___ |  \   |   ___] |  | |___ |  \ | |    | |___ |___ |  | |  |  |   |  |___ |  \ ___] )";

    text_output = "1. Start Game\n"
                  "2. Load Game\n"
                  "3. Instructions\n"
                  "4. Credits\n"
                  "5. Exit\n\n"
                  "Please enter your choice\n\n"
                  "> "; // Main menu text

    Game::displayOutput(); // Display main menu
}