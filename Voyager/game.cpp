// User created libraries
#include "art.h"
#include "game.h"
#include "Rock.h"
#include "command.h"
#include "menu.h"
#include "planet.h"
#include "ship.h"
#include "inventoryh.h"

// Standard C++ libraries
#include <iostream>
#include <sstream>
#include <vector>
#include <sstream>
#include <array>

using namespace std;

// Function implementation for Rock class
std::vector<Rock> createMasterRockList() {
    std::cout << "Creating master rock list from code..." << std::endl;
    std::vector<Rock> allRocks;

    // Rock(name, description, elementType, value, resourceYielded, yieldAmount)
    allRocks.push_back(Rock("Basalt Shard",
                            "A dark, fine-grained volcanic rock.", "Volcanic",
                            10, "Iron", 5));
    allRocks.push_back(Rock("Pumice Stone",
                            "A very light and porous volcanic rock.",
                            "Volcanic", 5, "Sulfur", 10));
    allRocks.push_back(Rock("Iron Ore", "A rusty-red rock, heavy with metal.",
                            "Metallic", 25, "Iron", 20));
    allRocks.push_back(Rock("Ice Chunk", "A chunk of frozen, murky water.",
                            "Ice", 1, "Water", 10));
    allRocks.push_back(Rock("Sandstone", "A common sedimentary rock.", "Desert",
                            2, "Silicon", 3));
    allRocks.push_back(Rock("Petrified Wood", "Ancient wood turned to stone.",
                            "Forest", 15, "Carbon", 10));
    allRocks.push_back(Rock("Barren Stone", "A simple, useless rock.", "Barren",
                            0, "Gravel", 1));

    std::cout << "Successfully created " << allRocks.size() << " rocks."
              << std::endl;
    return allRocks;
}

// Function implementation for Game class

Game::Game()
    : art_output(""), body_output(""), error_output(""), onMenu(false),
      onShip(false), onPlanet(false), gameOver(false), saved(false),
      next(false) {}

/*
Setters and getters for all outputs and game state flags
*/

void Game::setArtOutput(const string& art) { art_output = art; }
void Game::setBodyOutput(const string& body) { body_output = body; }
void Game::setErrorOutput(const string& error) { error_output = error; }

void Game::setMenuFlag(const bool& flag) { onMenu = flag; }
void Game::setShipFlag(const bool& flag) { onShip = flag; }
void Game::setPlanetFlag(const bool& flag) { onPlanet = flag; }
void Game::setGameOverFlag(const bool& flag) { gameOver = flag; }
void Game::setNextFlag(const bool& flag) { next = flag; }
void Game::setSavedFlag(const bool& flag) { saved = flag; }

string Game::getArtOutput() const { return art_output; }
string Game::getBodyOutput() const { return body_output; }
string Game::getErrorOutput() const { return error_output; }

bool Game::getMenuFlag() const { return onMenu; }
bool Game::getShipFlag() const { return onShip; }
bool Game::getPlanetFlag() const { return onPlanet; }
bool Game::getGameOverFlag() const { return gameOver; }
bool Game::getNextFlag() const { return next; }
bool Game::getSavedFlag() const { return saved; }

/*
Each if statement checks the command size, command content, and
then the game state, and will return the corresponding command.
These will be used in the game loop to manage core logic behind
commands
*/

Game::ValidCommand Game::checkCommand(const Command& command,
                                      const Game& game) const {
    const auto& input = command.getInput();
    if (input.empty() && !game.getNextFlag()) {
        return ValidCommand::Error;
    }
    else if (input.size() >= 1 && input[0] == "collect" &&
             game.getPlanetFlag()) {
        return ValidCommand::Collect;
    }
    else if (input.size() == 1 && input[0] == "credits" && game.getMenuFlag()) {
        return ValidCommand::Credits;
    }
    else if (input.size() >= 2 && input[0] == "drop" && game.getPlanetFlag()) {
        return ValidCommand::Drop;
    }
    else if (input.size() == 1 && input[0] == "exit" && game.getMenuFlag()) {
        return ValidCommand::Exit;
    }
    else if (input.size() >= 3 && input[0] == "inspect" && input[1] == "rock") {
        return ValidCommand::InspectRock;
    }
    else if (input.size() == 1 && (input[0] == "inventory" || input[0] == "inv") && !game.getMenuFlag()) {
        return ValidCommand::Inventory;
    }
    else if (input.size() == 1 && input[0] == "instructions" &&
             game.getMenuFlag()) {
        return ValidCommand::Instructions;
    }
    else if (((input.size() == 1 && input[0] == "back") ||
              (input.size() == 1 && input[0] == "menu") ||
              (input.size() >= 2 && input[0] == "main" &&
               input[1] == "menu")) &&
             game.getMenuFlag()) {
        return ValidCommand::MainMenu;
    }
    else if (((input.size() == 1 && input[0] == "load") ||
              (input.size() >= 2 && input[0] == "load" &&
               input[1] == "game")) &&
             game.getMenuFlag()) {
        return ValidCommand::Load;
    }
    else if ((input.empty() || (input.size() == 1 && input[0] == "next")) &&
             game.getNextFlag()) {
        return ValidCommand::Next;
    }
    else if ((input.size() == 3 && input[0] == "return" && input[1] == "to" &&
        input[2] == "ship") &&
        game.getPlanetFlag()) {
        return ValidCommand::ReturnToShip;
    }
    else if ((input.size() == 1 && input[0] == "save") ||
             (input.size() >= 2 && input[0] == "save" && input[1] == "game") &&
                 !game.getMenuFlag()) {
        return ValidCommand::Save;
    }
    else if (input.size() == 1 && input[0] == "scan" && game.getPlanetFlag()) {
        return ValidCommand::Scan;
    }
    else if (input.size() == 2 && input[0] == "exit" &&
             input[1] == "ship" && game.getShipFlag()) {
        return ValidCommand::ShipExit;
    }
    else if (((input.size() == 1 && input[0] == "menu") ||
        (input.size() >= 2 && input[0] == "main" &&
            input[1] == "menu")) &&
        game.getShipFlag() && game.getSavedFlag()) {
        return ValidCommand::ShipMainMenu;
    }
    else if (input.size() == 1 && input[0] == "scan" && game.getShipFlag()) {
        return ValidCommand::ScanForPlanets;
    }
    else if (((input.size() == 1 && input[0] == "start") ||
              (input.size() >= 2 && input[0] == "start" &&
               input[1] == "game")) &&
             game.getMenuFlag()) {
        return ValidCommand::Start;
    }
    else if (input.size() >= 3 && input[0] == "travel" &&
             game.getShipFlag()) {
        return ValidCommand::Travel;
    }
    else {
        return ValidCommand::Error;
    }
}

/*
This function checks to see what operating system the game is running on, either
Windows, or some Unix-based OS like Linux or MacOS. It will then run the
corresponding command to clear the terminal. A clean and easy way to implement
cross compatibility into our game
*/

void Game::clearScreen() const {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/*
This function combines the values for art, body, and error and displays all of
that as one output.
*/

void Game::displayOutput() const {
    string output =
        getArtOutput() + "\n\n" + getBodyOutput() + "\n\n" + getErrorOutput();
    cout << output;
}

void Game::saveGame() {}

/*
The game loop is the heart of the game. It will handle all of the displaying of
outputs as well as the logic behind each command.
*/

void Game::gameLoop(Game& game) const { 
    // initializations for initial game objects
    Menu menu;
    Command command;
    Ship ship;
    Art art;

    PlanetSystem planetSystem;
    vector<Rock> allGameRocks = createMasterRockList();

    Inventory playerInventory(20); 
    int currentPlanetIndex = -1; 

    string error; // string to store error messages

    game.setMenuFlag(true);
    menu.setMenu(game);

    while (!game.getGameOverFlag()) {

        /*
        Display the main menu initially and then take input.
        Contents of the display will be updated in the switch case
        */

        game.displayOutput();
        command.setInput();

        /*
        This is where all of the command logic will be stored. It will go over
        each enum value in ValidCommand and run the corresponding logic behind
        each command
        */

        ostringstream travelMsg;
        string art_text; //Temp variable for ASCII art
        string body_text; // Temp variable for body text
        const auto& input = command.getInput();
        int index;

        string inventoryMessage;
        Planet activePlanet;
        ValidCommand passedCommand = game.checkCommand(command, game);
        switch (passedCommand) {
        case ValidCommand::Collect:
            if (currentPlanetIndex != -1) {
                activePlanet = ship.getCurrentPlanet();

                Biome planetBiome = activePlanet.getBiome();

                // Convert the planet's Biome enum to a std::string to match your Rock class
                std::string targetRockType = "Barren"; 
                switch (planetBiome) {
                case Biome::Volcanic:
                    targetRockType = "Volcanic";
                    break;
                case Biome::Ice:
                case Biome::Ocean:
                    targetRockType = "Ice";
                    break;
                case Biome::Desert:
                    targetRockType = "Desert";
                    break;
                case Biome::Forest:
                    targetRockType = "Forest";
                    break;
                case Biome::GasGiant:
                case Biome::Urban:
                    targetRockType = "Metallic";
                    break;
                case Biome::Barren:
                default:
                    targetRockType = "Barren"; 
                    break;
                }

                Rock rockToCollect;
                bool foundRock = false;

                // Find a rock from the master list that matches the planet's string type
                for (const auto& rock : allGameRocks) {
                    if (rock.getElementType() == targetRockType) {
                        rockToCollect = rock; 
                        foundRock = true;
                        break; 
                    }
                }

                if (foundRock) {
                    // Try to add the rock, which fills inventoryMessage
                    if (playerInventory.addRock(rockToCollect, inventoryMessage)) {
                        game.setBodyOutput(inventoryMessage);
                        game.setErrorOutput("");
                    }
                    else {
                        game.setBodyOutput("");
                        game.setErrorOutput(inventoryMessage + "\n\n");
                    }
                }
                else {
                    game.setBodyOutput("You scan the area but find no valuable rocks of this planet's type.");
                    game.setErrorOutput("");
                }
            }
            else {
                game.setErrorOutput("ERR: You must be on a planet to collect rocks.\n\n");
            }
            break;

        case ValidCommand::Credits:
            menu.setCredits(game);
            break;
        case ValidCommand::Drop:
        { // Added curly braces to create a new scope for variables
            if (input.size() < 2) {
                game.setErrorOutput("ERR: What do you want to drop? (e.g., drop Basalt Shard)\n\n");
                break;
            }

            // Combine all words after "drop" into a single string
            std::string rockToDrop;
            for (size_t i = 1; i < input.size(); ++i) {
                rockToDrop += input[i] + (i == input.size() - 1 ? "" : " ");
            }

            if (playerInventory.removeRock(rockToDrop, inventoryMessage)) {
                game.setBodyOutput(inventoryMessage);
                game.setErrorOutput("");
            }
            else {
                game.setBodyOutput("");
                game.setErrorOutput(inventoryMessage); 
            }
        }
        break;
        case ValidCommand::Error:
            error = "ERR: Please enter a valid input\n\n";
            game.setErrorOutput(error);
            break;
        case ValidCommand::Exit:
            game.setGameOverFlag(true);
            break;
        case ValidCommand::InspectRock:
        { // Added curly braces for scope
            if (input.size() < 3) {
                game.setErrorOutput("ERR: What rock do you want to inspect? (e.g., inspect rock Basalt Shard)\n\n");
                break;
            }

            // Combine all words after "inspect rock"
            std::string rockToInspect;
            for (size_t i = 2; i < input.size(); ++i) {
                rockToInspect += input[i] + (i == input.size() - 1 ? "" : " ");
            }

            // inspectRock returns the full string, success or error
            std::string inspectResult = playerInventory.inspectRock(rockToInspect);
            if (inspectResult.rfind("ERR:", 0) == 0) { // Check if string starts with "ERR:"
                game.setBodyOutput("");
                game.setErrorOutput(inspectResult);
            }
            else {
                game.setBodyOutput(inspectResult);
                game.setErrorOutput("");
            }
        }
        break;
        case ValidCommand::Inventory:
            playerInventory.autoSortRocks(); // Sort before displaying
            game.setBodyOutput(playerInventory.getDisplayString());
            game.setErrorOutput("");
            break;
        case ValidCommand::Instructions:
            menu.setInstructions(game);
            break;
        case ValidCommand::Load:
            break;
        case ValidCommand::MainMenu:
            menu.setMenu(game);
            break;
        case ValidCommand::Next:
            game.setNextFlag(false);
            game.setMenuFlag(false);
            game.setShipFlag(true);
            body_text = "The view of space is unlike anything you have seen before.\nYou feel a sense of calm wash over you.";
            art.setArtToShip();
            game.setBodyOutput(body_text);
            game.setArtOutput(art.getArt());
            break;
        case ValidCommand::ReturnToShip:
            game.setPlanetFlag(false);
            game.setShipFlag(true);
            body_text = "You return to the ship.";
            game.setBodyOutput(body_text);
            art.setArtToShip();
            game.setArtOutput(art.getArt());
            break;
        case ValidCommand::Save:
            game.saveGame();
            break;
        case ValidCommand::Scan:
            activePlanet = ship.getCurrentPlanet();
            game.setBodyOutput(activePlanet.describe() + activePlanet.listRocks());
            game.setErrorOutput("Scan complete. Resources listed.");
            break;
        case ValidCommand::ShipExit:
            // First, check if we are actually at a planet
            ship.shipExit(game);
            break;
        case ValidCommand::ShipMainMenu:
            menu.setMenu(game);
            game.setMenuFlag(true);
            game.setShipFlag(false);
            break;
        case ValidCommand::ScanForPlanets:
            ship.getNearbyPlanet(game, planetSystem.getPlanetList());
            break;
        case ValidCommand::Start:
            game.setMenuFlag(false);
            game.setNextFlag(true);
            menu.setIntro(game);
            planetSystem.generatePlanets(20, allGameRocks);
            break;
        case ValidCommand::Travel:
            try {
                if (input[1] == "-d" || input[1] == "--destination") {
                    index = stoi(input[2]);
                    if (index >= 0 && index < planetSystem.getPlanetList().size()) {
                        // If valid, travel and set all game flags
                        ship.travelToPlanet(game, index, art);
                        game.setPlanetFlag(true);
                        currentPlanetIndex = index; // <-- This is the main fix!
                        game.setArtOutput(art.getArt());
                    }
                    else {
                        // If invalid, set an error message
                        game.setErrorOutput("ERR: Invalid planet index. Use 'scan' to see available planets.\n\n");
                    }
                }
                else if (input[1] == "-p" || input[1] == "--position") {

                    
                    std::array<double, 3> position;
                    position[0] = stoi(input[2]);
                    position[1] = stoi(input[3]);
                    position[2] = stoi(input[4]);
                    ship.setCoordinates(position);
                    travelMsg << "set coordinates to (" << position[0] << ", "
                        << position[1] << ", " << position[2] << ",)";
                    game.setBodyOutput(travelMsg.str());
                }
            }
            catch (const invalid_argument& e) {
                error = "ERR: Invalid argument\n\n";
                game.setErrorOutput(error);
            }
            catch (const out_of_range& e) {
                error = "ERR: Argument is out of range\n\n";
                game.setErrorOutput(error);
            }
            break;
        default:
            error = "ERR: PLease enter a valid input\n\n";
            game.setErrorOutput(error);
            break;
        }
        game.clearScreen(); // Clear screen before start of next loop iteration
    }
}