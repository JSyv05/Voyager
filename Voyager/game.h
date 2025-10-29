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
    // Display elements
    std::string art_output;  
    std::string body_output;
    std::string error_output;

    // Gamestate flags
    bool onMenu;
    bool onShip;
    bool onPlanet;
    bool gameOver;
    bool saved;
    bool next;

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

    void clearScreen() const;
    void displayOutput() const;

    /*
    The game loop will handle all logic. It will initialize the main menu
    and then once in the loop it will display the output and then take in the 
    input. From there it will handle all game logic, and then clear
    */

    void gameLoop(Game&) const;
};

#endif