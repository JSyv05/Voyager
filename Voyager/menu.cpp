#include<iostream>

#include"command.h"
#include"game.h"
#include"menu.h"
#include"planet.h"

using namespace std;

void Menu::setMenu(Game& g) const {
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
    g.setBodyOutput(text); // Sets text to menu options
	// Implementation for setting up the main menu
}
void Menu::setInstructions(Game& g) const {
    string art = R"(
                :::     ::: :::::::: :::   :::  :::     :::::::: :::::::::::::::::::             
               :+:     :+::+:    :+::+:   :+::+: :+:  :+:    :+::+:       :+:    :+:              
              +:+     +:++:+    +:+ +:+ +:++:+   +:+ +:+       +:+       +:+    +:+               
             +#+     +:++#+    +:+  +#++:+#++:++#++::#:       +#++:++#  +#++:++#:                 
             +#+   +#+ +#+    +#+   +#+ +#+     +#++#+    +#+#+#       +#+  +#+                 
             #+#+#+#  #+#    #+#   #+# #+#     #+##+#    #+##+#       #+#    #+                  
              ###     ########    ### ###     ### ######## #############    ###)";

    string text = "the goal of Voyager is to collect as many samples as\n"
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

                "Type back to return to main menu";

    g.setArtOutput(art); // Sets art to instructions screen
    g.setBodyOutput(text); // Sets text to instructions
}

void Menu::setCredits(Game& g) const{
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

    g.setArtOutput(art);
    g.setBodyOutput(text);
}

void Menu::setError(Game& g) const {
    string error = "ERR: Please input a valid command";
    g.setErrorOutput(error);
}