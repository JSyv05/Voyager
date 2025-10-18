#include<iostream>

#include"command.h"
#include"game.h"
#include"menu.h"
#include"planet.h"

using namespace std;

Menu::Menu() = default;

void Menu::setMainMenu(Game& g) const {
    string art = R"(
                :::     ::: :::::::: :::   :::  :::     :::::::: :::::::::::::::::::             
               :+:     :+::+:    :+::+:   :+::+: :+:  :+:    :+::+:       :+:    :+:              
              +:+     +:++:+    +:+ +:+ +:++:+   +:+ +:+       +:+       +:+    +:+               
             +#+     +:++#+    +:+  +#++:+#++:++#++::#:       +#++:++#  +#++:++#:                 
             +#+   +#+ +#+    +#+   +#+ +#+     +#++#+    +#+#+#       +#+  +#+                 
             #+#+#+#  #+#    #+#   #+# #+#     #+##+#    #+##+#       #+#    #+                  
              ###     ########    ### ###     ### ######## #############    ###                   
____ _  _ ____ ____ _   _ ____ ____ ____ ____ _ ____ _ ____ ____ _  _ ____ ___ ___ ____ ____ ____ 
|___ |  | |___ |__/  \_/  [__  |__| |    |__/ | |___ | |    |___ |\/| |__|  |   |  |___ |__/ [__  
|___  \/  |___ |  \   |   ___] |  | |___ |  \ | |    | |___ |___ |  | |  |  |   |  |___ |  \ ___] )"; // ASCII art title screen ooooooo

    string err = ""; // Clear error output

    string text = "> Start Game\n"
                       "> Load Game\n"
                       "> Instructions\n"
                       "> Credits\n"
                       "> Exit\n\n"
                       "Please enter your choice."; // Main menu text

    g.setArtOutput(art);   // Sets art to title screen
    g.setErrorOutput(err); // Clears error output
    g.setTextOutput(text); // Sets text to menu options
	// Implementation for setting up the main menu
}

void Menu::MainMenu(Command c, Game g) const {

    /*
    This is the command parser For the main menu.
    It will take the tokenized command and then check each of the indices for
    keywords to run commands. There should be a command parser for each setting
    in the game, such as on planets, on the ship, in space, etc. The command
    parser will be a while loop that will continue until the user exits the
    given area. The command parser will also be able to handle invalid commands
    and return an error message. Each if statement will check each index of the
    tokenized command for keywords. Most of the time, the first index will be
    the command, and any following indices will be arguments.
    */

    bool start_game = false; // Reset start_game to false whenever we enter the main menu loop

    setMainMenu(g); // Display main menu
    while (!start_game) {
        g.clearScreen();
        g.displayOutput();             // Display output
        c.setInput();                  // Set input
        auto& command = *c.getInput(); // Alias for easier access to command vector
        if (command.empty()) {   // If no input is given
            string err =
                "ERR) Invalid input. Please enter a valid command."; // returns
                                                                     // an error
                                                                     // message
            g.setErrorOutput(err);
        }
        else if ((command.size() >= 1 && command[0] == "start") ||
                 (command.size() >= 2 && command[0] == "start" &&
                  command[1] == "game")) {
            start_game = true;
            showIntro(g);
        }
        else if ((command.size() >= 1 && command[0] == "load") ||
                 (command.size() >= 2 && command[0] == "load" &&
                  command[1] == "game")) {
            start_game = true;

                       string err = ""; // Clear error output
            g.setErrorOutput(err);
        }
        else if (command[0] == "instructions") {
            string text =
                "the goal of Voyageer is to collect as many samples as "
                "possible,\n"
                "explore as many planets as possible, and then return to Earth "
                "safely.\n"
                "You will be able to use commands to navigate around the solar "
                "system \n"
                "simply by typing in a 2-4 word command.\n"
                "(\"Examine Granite\", \"Trade meat with merchant\", etc.)\n\n"
                "The challenge is resource management. You will have to spend "
                "samples\n"
                "to maintain the health of your ship and yourself. You will "
                "also\n"
                "lose resources from random events that will occur.You will "
                "have to make\n"
                "strategic decisions on what to spend resources on as well as "
                "what items\n"
                "you need to survive.\n\n"
                "When it comes to space exploration, there is only one saying: "
                "\"Every Sacrifice Matters\"\n\n"
                "Type back to return to main menu"; // Instructions and game
                                                    // overview
            g.setTextOutput(text);

            string err = ""; // Clear error output
            g.setErrorOutput(err);
        }
        else if (command[0] == "credits") {
            string text =
                "Team Members:\nAlina Betances\nAnthony Pinto\nElias "
                "Reeves\nMatthew Silva\nJohn Syvertsen\n\n"
                "Scrum Master:\nJohn Syvertsen\n\n"
                "Programmers:\nAlina Betances\nAnthony Pinto\nElias "
                "Reeves\nMatthew Silve\nJohn Syvertsen\n\n"
                "Type back to return to the main menu."; // will show credits.
                                                         // To be implemented
                                                         // later
            g.setTextOutput(text);

            string err = ""; // Clear error output
            g.setErrorOutput(err);
        }
        else if (command[0] == "exit") {
            g.clearScreen();
            exit(0); // Exit the game
        }
        else if (command[0] == "back") {
            setMainMenu(g); // Go back to main menu
        }
        else {
            string err =
                "ERR) Invalid input. Please enter a valid command."; // returns
                                                                     // an error
                                                                     // message
            g.setErrorOutput(err);
        }
    }
    // Implementation for displaying the main menu
}

//Intro Story
void Menu::showIntro(Game& g) const
{
    g.clearScreen();
    string introText = "Captain's Log, Stardate 2247.03...\n\n"
        "After decades of preparation, the Voyager Initiative has finally launched.\n"
        "Our mission: explore the outer systems, gather samples from uncharted worlds,\n"
        "and return home before the fuel cells run dry.\n\n"
        "Each planet brings its own challenges - extreme heat, toxic winds, frozen storms.\n"
        "But every discovery pushes humanity one step closer to survival.\n\n"
        "You are the last hope of the Voyager fleet.\n"
        "Remember: every sacrifice matters.\n\n"
        "Type 'next' and press Enter to continue...";

    g.setArtOutput("");
    g.setErrorOutput("");
    g.setTextOutput(introText);
    g.displayOutput();

    waitForNextKey();

    g.clearScreen();
    PlanetSystem planetSystem;
    planetSystem.run(g);
}

//Wait for 'next'
void Menu::waitForNextKey() const
{
    Command c;
    while (true)
    {
        c.setInput();
        if (!c.getInput()->empty() && (*c.getInput())[0] == "next")
        {  break; }
    }
}