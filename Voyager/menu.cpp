#include<iostream>

#include"command.h"
#include"game.h"
#include"menu.h"
#include"planet.h"

using namespace std;

void Menu::setMenu(Game& game) const {
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

    string text = 
        "> Start Game\n"
        "> Load Game\n"
        "> Instructions\n"
        "> Credits\n"
        "> Exit\n\n"

        "Please enter your choice."; // Main menu text

    game.setArtOutput(art);   // Sets art to title screen
    game.setErrorOutput("");  // Clears error output
    game.setBodyOutput(text); // Sets text to menu options
	// Implementation for setting up the main menu
}
void Menu::setInstructions(Game& game) const {
    string art = R"(
                :::     ::: :::::::: :::   :::  :::     :::::::: :::::::::::::::::::             
               :+:     :+::+:    :+::+:   :+::+: :+:  :+:    :+::+:       :+:    :+:              
              +:+     +:++:+    +:+ +:+ +:++:+   +:+ +:+       +:+       +:+    +:+               
             +#+     +:++#+    +:+  +#++:+#++:++#++::#:       +#++:++#  +#++:++#:                 
             +#+   +#+ +#+    +#+   +#+ +#+     +#++#+    +#+#+#       +#+  +#+                 
             #+#+#+#  #+#    #+#   #+# #+#     #+##+#    #+##+#       #+#    #+                  
              ###     ########    ### ###     ### ######## #############    ###)";

    string text = 
        "the goal of Voyager is to collect as many samples as\n"
        "possible, explore as many planets as possible, and then\n" 
        "return to Earth safely. You will be able to use commands\n"
        "to navigate around the solar system simply by typing in a\n"
        "simple word command.\n"
        "(\"Examine Granite\", \"Trade meat with merchant\", etc.)\n\n"

        "The challenge is resource management. You will have to spend\n"
        "samples to maintain the health of your ship and yourself. You will\n"
        "also lose resources from random events that will occur. You will\n"
        "have to make strategic decisions on what to spend resources on as\n"
        "well as what items you need to survive.\n\n"

        "When it comes to space exploration, there is only one saying:\n\n"
        "\"Every Sacrifice Matters\"\n\n"

        "Type 'back' to return to main menu ";

    game.setArtOutput(art); // Sets art to instructions screen
    game.setErrorOutput("");
    game.setBodyOutput(text); // Sets text to instructions
}

void Menu::setCredits(Game& game) const{
    string art = R"(
                :::     ::: :::::::: :::   :::  :::     :::::::: :::::::::::::::::::             
               :+:     :+::+:    :+::+:   :+::+: :+:  :+:    :+::+:       :+:    :+:              
              +:+     +:++:+    +:+ +:+ +:++:+   +:+ +:+       +:+       +:+    +:+               
             +#+     +:++#+    +:+  +#++:+#++:++#++::#:       +#++:++#  +#++:++#:                 
             +#+   +#+ +#+    +#+   +#+ +#+     +#++#+    +#+#+#       +#+  +#+                 
             #+#+#+#  #+#    #+#   #+# #+#     #+##+#    #+##+#       #+#    #+                  
              ###     ########    ### ###     ### ######## #############    ###)";

    string text = "Team Members:\nAlina Betances\nAnthony Pinto\nElias "
                  "Reeves\nMatthew Silva\nJohn Syvertsen\n\n"
                  "Scrum Master:\nJohn Syvertsen\n\n"
                  "Programmers:\nAlina Betances\nAnthony Pinto\nElias "
                  "Reeves\nMatthew Silva\nJohn Syvertsen\n\n"
                  "Type back to return to the main menu.";

    game.setArtOutput(art);
    game.setBodyOutput(text);
    game.setErrorOutput("");
}

void Menu::setIntro(Game& game) const{
    string art = R"(
       <<Legions of Earth>>
        .---.        .---.
       /     \  __  /     \
      / /     \(  )/     \ \
     //////   ' \/ `   \\\\\\
    //// / // :    : \\ \ \\\\
   // /   /  /`    '\  \   \ \\
  //          //..\\  /-/  |   \
        <====UU====UU====--O--
             '//||\\` \-\  |
               ''``
  <<Dept. of Space Exploration>>)";

    string text = 
        "VOYAGER PROGRAM: LOG ALPHA-01\n\n"

        "After decades of preparation, the Voyager Program has finally launched.\n"
        "Our mission: explore the outer systems, gather samples from uncharted\n"
        "worlds, and return home before the fuel cells run dry.\n\n"

        "Each planet brings its own challenge, but every discovery will push\n"
        "humanity one step closer to glory.\n\n"

        "You are going to be the start of Humanities duty to explore the galaxy.\n\n"
        "Remember, Voyager: \"Every Sacrifice Matters\".\n\n"

        "- Grand Overseer of the Legion Atreitus\n\n"

        "Type 'next' and press Enter to continue...";

    game.setArtOutput(art);
    game.setBodyOutput(text);
    game.setErrorOutput("");
}

void Menu::setError(Game& game) const {
    string error = "ERR: Please input a valid command\n\n";
    game.setErrorOutput(error);
}