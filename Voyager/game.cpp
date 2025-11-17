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
#include <array>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// Function implementation for Rock class

//TODO: 
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
    next(false) {
}

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

Game::ValidCommand Game::checkCommand(const Command& command) const {
    const auto& input = command.getInput();
    if (input.empty() && !getNextFlag()) {
        return ValidCommand::Error;
    }
    else if (input.size() >= 1 && input[0] == "collect" &&
        getPlanetFlag()) {
        return ValidCommand::Collect;
    }
    else if (input.size() == 1 && input[0] == "credits" && getMenuFlag()) {
        return ValidCommand::Credits;
    }
    else if (input.size() >= 2 && input[0] == "drop" && getPlanetFlag()) {
        return ValidCommand::Drop;
    }
    else if (input.size() == 1 && input[0] == "exit" && getMenuFlag()) {
        return ValidCommand::Exit;
    }
    else if (input.size() >= 3 && input[0] == "inspect" && input[1] == "rock") {
        return ValidCommand::InspectRock;
    }
    else if (input.size() == 1 && (input[0] == "inventory" || input[0] == "inv") && !getMenuFlag()) {
        return ValidCommand::Inventory;
    }
    else if (input.size() == 1 && input[0] == "instructions" &&
        getMenuFlag()) {
        return ValidCommand::Instructions;
    }
    else if (((input.size() == 1 && input[0] == "back") ||
        (input.size() == 1 && input[0] == "menu") ||
        (input.size() >= 2 && input[0] == "main" &&
            input[1] == "menu")) &&
        getMenuFlag()) {
        return ValidCommand::MainMenu;
    }
    else if (((input.size() == 1 && input[0] == "load") ||
        (input.size() >= 2 && input[0] == "load" &&
            input[1] == "game")) &&
        getMenuFlag()) {
        return ValidCommand::Load;
    }
    else if ((input.empty() || (input.size() == 1 && input[0] == "next")) &&
        getNextFlag()) {
        return ValidCommand::Next;
    }
    else if ((input.size() == 3 && input[0] == "return" && input[1] == "to" &&
        input[2] == "ship") &&
        getPlanetFlag()) {
        return ValidCommand::ReturnToShip;
    }
    else if ((input.size() == 1 && input[0] == "save") ||
        (input.size() >= 2 && input[0] == "save" && input[1] == "game") &&
        !getMenuFlag()) {
        return ValidCommand::Save;
    }
    else if (input.size() >= 2 && input[0] == "scan" && input[1] == "-a" && getPlanetFlag()) {
        return ValidCommand::Scan;
    }
    else if (input.size() == 2 && input[0] == "exit" &&
             input[1] == "ship" && getShipFlag()) {
        return ValidCommand::ShipExit;
    }
    else if (((input.size() == 1 && input[0] == "menu") ||
        (input.size() >= 2 && input[0] == "main" &&
            input[1] == "menu")) &&
        getShipFlag() && getSavedFlag()) {
        return ValidCommand::ShipMainMenu;
    }
    else if (input.size() >= 2 && input[0] == "scan" && input[1] == "-p" && getShipFlag()) {
        return ValidCommand::ScanForPlanets;
    }
    else if (input.size() == 1 && input[0] == "scan") {
        return ValidCommand::Error; // or a special Help command if you want
    }
    else if (((input.size() == 1 && input[0] == "start") ||
        (input.size() >= 2 && input[0] == "start" &&
            input[1] == "game")) &&
        getMenuFlag()) {
        return ValidCommand::Start;
    }
    else if (input.size() >= 3 && input[0] == "travel" &&
             getShipFlag()) {
        return ValidCommand::Travel;
    }
    else if (input.size() >= 3 && input[0] == "talk" && input[1] == "to")
    {
        return ValidCommand::Talk;
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
    ostringstream output;
    output << getArtOutput() << "\n\n" << getBodyOutput() << "\n\n" <<
                    getErrorOutput();

    if (getErrorOutput() != "") {
        output << "\n\n";
    }
    cout << output.str();
}

void Game::saveGame() {}

/*
The game loop is the heart of the game. It will handle all of the displaying of
outputs as well as the logic behind each command.
*/

void Game::gameLoop() { 
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

    setMenuFlag(true);
    art.setArtToTitle();
    setBodyOutput(menu.setMenu());

    while (!getGameOverFlag()) {

        /*
        Display the main menu initially and then take input.
        Contents of the display will be updated in the switch case
        */
        setArtOutput(art.getArt());
        displayOutput();
        command.setInput();

        setErrorOutput("");

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
        ValidCommand passedCommand = checkCommand(command);
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
                        setBodyOutput(inventoryMessage);
                        setErrorOutput("");
                    }
                    else {
                        setBodyOutput("");
                        setErrorOutput(inventoryMessage);
                    }
                }
                else {
                    setBodyOutput("You scan the area but find no valuable rocks of this planet's type.");
                }
            }
            else {
                setErrorOutput("ERR: You must be on a planet to collect rocks.\n\n");
            }
            break;

        case ValidCommand::Credits:
            setBodyOutput(menu.setCredits());
            break;
        case ValidCommand::Drop:
        { // Added curly braces to create a new scope for variables
            if (input.size() < 2) {
                setErrorOutput("ERR: What do you want to drop? (e.g., drop Basalt Shard)");
                break;
            }

            // Combine all words after "drop" into a single string
            std::string rockToDrop;
            for (size_t i = 1; i < input.size(); ++i) {
                rockToDrop += input[i] + (i == input.size() - 1 ? "" : " ");
            }

            if (playerInventory.removeRock(rockToDrop, inventoryMessage)) {
                setBodyOutput(inventoryMessage);
            }
            else {
                setBodyOutput("");
                setErrorOutput(inventoryMessage); 
            }
        }
        break;
        case ValidCommand::Error:
            error = "ERR: Please enter a valid input";
            setErrorOutput(error);
            break;
        case ValidCommand::Exit:
            setGameOverFlag(true);
            break;
        case ValidCommand::InspectRock:
        { // Added curly braces for scope
            if (input.size() < 3) {
                setErrorOutput("ERR: What rock do you want to inspect? (e.g., inspect rock Basalt Shard)");
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
                setBodyOutput("");
                setErrorOutput(inspectResult);
            }
            else {
                setBodyOutput(inspectResult);
            }
        }
        break;
        case ValidCommand::Inventory:
            playerInventory.autoSortRocks(); // Sort before displaying
            setBodyOutput(playerInventory.getDisplayString());
            break;
        case ValidCommand::Instructions:
            setBodyOutput(menu.setInstructions());
            break;
        case ValidCommand::Load:
            break;
        case ValidCommand::MainMenu:
            setBodyOutput(menu.setMenu());
            break;
        case ValidCommand::Next:
            setMenuFlag(false);
            setNextFlag(false);
            setShipFlag(true);
            body_text = "The view of space is unlike anything you have seen before.\nYou feel a sense of calm wash over you.\n(use scan -p to scan for nearby planets)";
            art.setArtToShip();
            setBodyOutput(body_text);
            break;
        case ValidCommand::ReturnToShip:
            setPlanetFlag(false);
            setShipFlag(true);
            setBodyOutput(ship.returnToShip());
            art.setArtToShip();
            break;
        case ValidCommand::Save:
            saveGame();
            break;
        case ValidCommand::Scan:
            activePlanet = ship.getCurrentPlanet();
            setBodyOutput(activePlanet.describe() +
                               activePlanet.listRocks() +
                               activePlanet.listPlantsOnPlanet()+ 
            activePlanet.listNPCs());
            setErrorOutput("Scan complete. Resources listed.");
            break;
        case ValidCommand::ShipExit:
            // First, check if we are actually at a planet
            setBodyOutput(ship.shipExit());
            setShipFlag(false);
            setPlanetFlag(true);
            break;
        case ValidCommand::ShipMainMenu:
            setBodyOutput(menu.setMenu());
            setMenuFlag(true);
            setShipFlag(false);
            break;
        case ValidCommand::ScanForPlanets:
            setBodyOutput(ship.getNearbyPlanet(planetSystem.getPlanetList()));
            break;
        case ValidCommand::Start:
            setMenuFlag(false);
            setNextFlag(true);
            setBodyOutput(menu.setIntro());
            art.setArtToAguila();
            planetSystem.generatePlanets(20, allGameRocks);
            break;
        case ValidCommand::Travel:
            try {
                if (input[1] == "-d" || input[1] == "--destination") {
                    index = stoi(input[2]);
                        // If valid, travel and set all game flags
                    setBodyOutput(ship.travelToPlanet(index, art));
                }
                else if (input[1] == "-p" || input[1] == "--position") {
                    std::array<double, 3> position;
                    position[0] = stoi(input[2]);
                    position[1] = stoi(input[3]);
                    position[2] = stoi(input[4]);
                    ship.setCoordinates(position);
                    travelMsg << "set coordinates to (" << position[0] << ", "
                        << position[1] << ", " << position[2] << ")";
                    setBodyOutput(travelMsg.str());
                }
                else {
                    error = "ERR: Please pass a valid flag";
                    setBodyOutput(error);
                }
            }
            catch (const invalid_argument& e) {
                error = "ERR: Invalid argument";
                setErrorOutput(error);
            }
            catch (const out_of_range& e) {
                error = "ERR: Argument is out of range";
                setErrorOutput(error);
            }
            break;
        case ValidCommand::Talk:
        {
            int npcIndex = 0;
            try { npcIndex = stoi(input[2]); }
            catch (...) { npcIndex = 0; }

            ostringstream msg;
            msg << ship.getCurrentPlanet().talkToNPC(npcIndex) << "\n";

            setBodyOutput(msg.str());
            break;
        }
        default:
            error = "ERR: PLease enter a valid input";
            setErrorOutput(error);
            break;
        }
        clearScreen(); // Clear screen before start of next loop iteration
    }
}