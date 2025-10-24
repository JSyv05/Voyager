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