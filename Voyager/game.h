#ifndef GAME_H
#define GAME_H

#include"command.h"

#include <string>

/*
The function of the Game class is to manage the overall state and flow of the game.
It handles all text and art output, manages the game loop, and keeps track
of the game state that we are in (on menu, on ship, on planet, etc.).
*/

class Game {
private:
    std::string art_output;   // Art output
    std::string body_output;  // Text output
    std::string error_output; // Error output
    bool onMenu; // Flag to check if in menu screen
    bool onShip; // Flag to check if on the ship
    bool onPlanet; // Flag to check if we are on a planet
    bool gameOver; // Flag to check if game is over
    bool saved; // Flag to check if the game has been saved
    bool next; // Flag for any ingame events that require the next command

    /*
    Valid command will keep track of all possible commands in the game. The command parser checkCommand()
    will then check the command and the game state to return each of these enum values
    */
    enum class ValidCommand {
        Collect,
        Credits,
        Drop,
        Error,
        Exit,
        Instructions,
        Load,
        MainMenu,
        Next,
        ReturnToShip,
        Save,
        Scan,
        ShipExit,
        ShipMainMenu,
        ScanForPlanets,
        Start,
        Travel,
    };
public:
    Game(); // Default constructor

    /*
    Getters and setters will be utilized a lot in this project.
    Getters are used to set up text and to see the current game state,
    and setters are used to change game states and to change the display.
    */

    void setBodyOutput(const std::string&);
    void setArtOutput(const std::string&);   
    void setErrorOutput(const std::string&);
    void setMenuFlag(const bool&);
    void setShipFlag(const bool&);
    void setPlanetFlag(const bool&);
    void setGameOverFlag(const bool&);
    void setNextFlag(const bool&);
    void setSavedFlag(const bool&);

    std::string getBodyOutput() const;      
    std::string getArtOutput() const;       
    std::string getErrorOutput() const;     
    bool getMenuFlag() const;
    bool getShipFlag() const;
    bool getPlanetFlag() const;
    bool getGameOverFlag() const;
    bool getNextFlag() const;
    bool getSavedFlag() const;

    void saveGame();

    /*
    The check function will check .
    */ 
    ValidCommand checkCommand(Command&, Game&) const;

    /*
    These are the UI commands. They will handle clearing and updating
    the display of the game
    */

    void clearScreen() const;   // Clears the console screen
    void displayOutput() const; // Displays text, art, and input field

    /*
    The game loop will handle all logic. It will initialize the main menu
    and begin taking in inputs. The game loop will broken up by game state,
    with if and else if statements controlling what happens depending on what
    the current game state is. Each if statement contains both the check 
    commands for each enum, and a switch case that will determine what happens 
    when a certain case is met.
    */

    void gameLoop(Game&) const; // Main game loop
};

#endif