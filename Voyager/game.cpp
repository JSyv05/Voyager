// User created libraries
#include "art.h"
#include "game.h"
#include "Rock.h"
#include "command.h"
#include "menu.h"
#include "help.h"
#include "planet.h"
#include "ship.h"
#include "inventoryh.h"
#include "npc.h"

// Standard C++ libraries
#include <array>
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>

using namespace std;

vector<Rock> createMasterRockList();   // declare rock creation routine, a global in the rock class

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

// TODO: refactor checkCommand to use a map instead of if/else-if block

/*
Rather than have if/else-if statements, use a map with input[0] as the key, with the values being arrays of size 2,
the first value being a default return value if there is no flag, and the second being a map for flag return values.

string manip to store input[0] and input[1] as string variables command and flag

using namespace ValidCommand
map = {
    "collect": [Collect, null]
    "scan": [
        Scan, {
            "-a": scanAreaForSamples,
            "-p": scanForPlanets
        }
    ]
}

if flag?:
    return map[command][1][flag]
else: 
    return map[command][0]

Idea 2: break apart checkCommand into checkCommand by Flag
*/
Game::ValidCommand Game::checkCommand(const Command& command) const {
    const auto& input = command.getInput();
    if (input.empty() && !getNextFlag()) {
        return ValidCommand::Error;
    }
    else if (input.size() >= 1 && input[0] == "attack" && getPlanetFlag())
    {
        return ValidCommand::Attack;
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
    else if (input.size() == 1 && input[0] == "Quit" && getMenuFlag()) {
        return ValidCommand::Quit;
    }
    else if (input.size() == 1 && input[0] == "help" && !(getMenuFlag() || getNextFlag())) {
        return ValidCommand::Help;
    }
    else if (input.size() >= 3 && input[0] == "inspect" && input[1] == "rock") {
        return ValidCommand::InspectRock;
    }
    else if (input.size() == 1 && (input[0] == "inventory" || input[0] == "inv") && !(getMenuFlag() || getNextFlag())) {
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
    else if (input.size() == 3 && input[0] == "return" && input[1] == "to" &&
        input[2] == "ship" &&
        getPlanetFlag()) {
        return ValidCommand::ReturnToShip;
    }
    else if ((input.size() == 1 && input[0] == "save") ||
        (input.size() >= 2 && input[0] == "save" && input[1] == "game") &&
        !getMenuFlag()) {
        return ValidCommand::Save;
    }
    else if (input.size() == 1 && input[0] == "sneak" && getPlanetFlag())
    {
        return ValidCommand::Sneak;
    }
    else if (input.size() >= 1 && input[0] == "scan" && !(getMenuFlag() && getNextFlag())) {
        return ValidCommand::Scan;
    }
    else if (input.size() == 2 && input[0] == "exit" &&
             input[1] == "ship" && getShipFlag()) {
        return ValidCommand::Exit;
    }
    else if (((input.size() == 1 && input[0] == "menu") ||
        (input.size() >= 2 && input[0] == "main" &&
            input[1] == "menu")) &&
        getShipFlag() && getSavedFlag()) {
        return ValidCommand::ShipMainMenu;
    }
    else if (((input.size() == 1 && input[0] == "start") ||
        (input.size() >= 2 && input[0] == "start" &&
            input[1] == "game")) &&
        getMenuFlag()) {
        return ValidCommand::Start;
    }
    else if (input.size() >= 1 && input[0] == "travel" &&
             getShipFlag()) {
        return ValidCommand::Travel;
    }
    else if (input.size() == 1 && input[0] == "interact" && getPlanetFlag())
    {
        return ValidCommand::Talk;
    }
    else if (input.size() == 1 && input[0] == "health")
    {
        return ValidCommand::Health;
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

//Helper function to throw an error for travel -p

void checkInputSizeLessThanFive(const vector<string>& in_vector) {
    if (in_vector.size() < 5) {
        throw out_of_range("ERR: Not enough arguments for coordinate");
    }
}

// Helper function to get art based on planet type

string getArtForTravelToPlanet(Biome biome, Art art) {
    switch (biome) {
    case Biome::Desert:
        return art.setArtToDesert();
    case Biome::Ice:
        return art.setArtToIce();   
    case Biome::Ocean:
        return art.setArtToOcean();  
    case Biome::Forest:
        return art.setArtToForest();  
    case Biome::Volcanic:
        return art.setArtToVolcano();
    case Biome::GasGiant:
        return art.setArtToGasGiant();
    case Biome::Urban:
        return art.setArtToCity();
    case Biome::Barren:
        return art.setArtToWasteLand();
    default:
        return "ERR: Surface could not be processed";
    }
}

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
    Help help;

    PlanetSystem planet_system;
    vector<Rock> all_game_rocks = createMasterRockList();

    Inventory player_inventory(20);  

    int planetCommandCounter = 0; // counter inputs while on a planet
    bool playerIsSneaking = false;  // set by sneak command
    const int MONSTER_ATTACK_THRESHOLD = 5; // how many commands before auto-attack

    // New monster that persits while you're on the planet 
    unique_ptr<Monster> activeMonster;

    setMenuFlag(true);
    setArtOutput(art.setArtToTitle());
    setBodyOutput(menu.setMenu());

    while (!getGameOverFlag()) {

        /*
        Display the main menu initially and then take input.
        Contents of the display will be updated in the switch case
        */
        displayOutput();
        command.setInput();

        setErrorOutput("");

        /*
        This is where all of the command logic will be stored. It will go over
        each enum value in ValidCommand and run the corresponding logic behind
        each command
        */
        const auto& input = command.getInput();

        ValidCommand passed_command = checkCommand(command);
        switch (passed_command) {
        case ValidCommand::Attack:
        {
            if (!getPlanetFlag())
            {
                setErrorOutput("You can only attack while on a planet.");
                break;
            }

            // Lazily create a monster for this planet if we don't have one yet
            if (!activeMonster)
            {
                Planet& active_planet = ship.getCurrentPlanet();
                Biome biome = active_planet.getBiome();
                int difficulty = active_planet.getLootLevel();   // lootLevel_ is your difficulty

                activeMonster = make_unique<Monster> (createMonsterForBiomeAndDifficulty(biome, difficulty));
            }

            Monster& monster = *activeMonster;

            ostringstream summary;

            // Player's attack 
            int hpBefore = monster.getHealth();
            int dmgToMonster = player.dealDamage();
            monster.takeDamage(dmgToMonster);
            int hpAfter = monster.getHealth();

            summary << "You attack " << monster.getName()
                << " for " << dmgToMonster << " damage.\n"
                << monster.getName() << " HP: " << hpAfter << "\n";

            // Did you kill it with this hit?
            if (monster.isDead())
            {
                summary << "\nYou defeated " << monster.getName() << "!";
                activeMonster.reset();           // no monster until a new one is spawned
                playerIsSneaking = false;        // clear sneak
                setBodyOutput(summary.str());
                setErrorOutput("");
                break;
            }

            // --- Monster counter-attack (unless it was a sneak attack) ---
            if (playerIsSneaking)
            {
                // Sneak gives a free hit – no counter this turn
                summary << monster.getName()
                    << " is caught off guard and can't react!";
                playerIsSneaking = false;   // consume the sneak
            }
            else
            {
                // Monster hits back once
                summary << monster.attackPlayer(player) << "\n";

                if (player.isDead())
                {
                    summary << "You have been defeated by "
                        << monster.getName() << "...";
                    setGameOverFlag(true);
                }
            }

            setBodyOutput(summary.str());
            setErrorOutput("");
        }
        break;
        case ValidCommand::Collect: {
            Planet& active_planet = ship.getCurrentPlanet();  // will be mutating the rocks on the planet in this code

            // Rock Refactor (LV) - deleted code to decide rock to collect based on the biome
            //    Now take a rock from the planet - note - will remove the rock from the planet after collection
            //    If there are no rocks on the planet, collectRock... will return element type = "Generic"
            Rock rock = active_planet.collectRockOnPlanet();

            string inventory_message;

            if (rock.getElementType() != "Generic") {
                // Try to add the rock, which fills inventoryMessage
                if (player_inventory.addRock(rock, inventory_message)) {
                    setBodyOutput(inventory_message);
                    setErrorOutput("");
                }
                else {   // problem - couldn't add the rock to the inventory, but rock already deleted
                    // could ToDo possibly add a new planet method to add a rock and call it to replace the rock
                    // note - should create the method regardless - more intuitive and scalable
                    setBodyOutput("");
                    setErrorOutput(inventory_message);
                }
            }
            else {  // no rocks on the planet to collect
                setBodyOutput("You scan the area but find no valuable rocks of "
                              "this planet's type.");
            }
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
            string rockToDrop;
            for (size_t i = 1; i < input.size(); ++i) {
                rockToDrop += input[i] + (i == input.size() - 1 ? "" : " ");
            }


            string inventory_message;
            if (player_inventory.removeRock(rockToDrop, inventory_message)) {
                setBodyOutput(inventory_message);
            }
            else {
                setBodyOutput("");
                setErrorOutput(inventory_message); 
            }
        }
        break;

        case ValidCommand::Error: {
            string error = "ERR: Please enter a valid input";
            setErrorOutput(error);
        }
            break;

        case ValidCommand::Quit:
            setGameOverFlag(true);
            break;

        case ValidCommand::Help:
            setBodyOutput(help.getGeneralHelp());
            break;

        case ValidCommand::InspectRock:
        { // Added curly braces for scope
            if (input.size() < 3) {
                setErrorOutput("ERR: What rock do you want to inspect? (e.g., inspect rock Basalt Shard)");
                break;
            }

            // Combine all words after "inspect rock"
            string rock_to_inspect;
            for (size_t i = 2; i < input.size(); ++i) {
                rock_to_inspect += input[i] + (i == input.size() - 1 ? "" : " ");
            }

            // inspectRock returns the full string, success or error
            string inspect_result = player_inventory.inspectRock(rock_to_inspect);
            if (inspect_result.rfind("ERR:", 0) == 0) { // Check if string starts with "ERR:"
                setBodyOutput("");
                setErrorOutput(inspect_result);
            }
            else {
                setBodyOutput(inspect_result);
            }
        }
        break;

        case ValidCommand::Inventory:
            player_inventory.autoSortRocks(); // Sort before displaying
            setBodyOutput(player_inventory.getDisplayString());
            break;

        case ValidCommand::Instructions:
            setBodyOutput(menu.setInstructions());
            break;

        case ValidCommand::Load:
            break;

        case ValidCommand::MainMenu:
            setBodyOutput(menu.setMenu());
            break;

        case ValidCommand::Next: {
            setMenuFlag(false);
            setNextFlag(false);
            setShipFlag(true);

            string output =
                "The view of space is unlike anything you have seen "
                "before.\nYou feel a sense of calm wash over you.\n(use scan "
                "-p to scan for nearby planets)";
            setArtOutput(art.setArtToShip());
            setBodyOutput(output);
        }
            break;

        case ValidCommand::ReturnToShip:
            setPlanetFlag(false);
            setShipFlag(true);
            setBodyOutput(ship.returnToShip());
            setArtOutput(art.setArtToShip());
            break;

        case ValidCommand::Save:
            saveGame();
            break;

        case ValidCommand::Scan:
            if ((input.size() == 1) ||
                (input[1] == "-h" || input[1] == "--help")) {
                setBodyOutput(help.getScanHelp());
            }
            else if ((input[1] == "-a" || input[1] == "--area") && getPlanetFlag()) {
                Planet& active_planet = ship.getCurrentPlanet();
                setBodyOutput(active_planet.describe() +
                              active_planet.listRocks() +
                              active_planet.listPlantsOnPlanet() +
                              active_planet.listNPCs());
                setErrorOutput("Scan complete. Resources listed.\n\n");
            }
            else if ((input[1] == "-p" || input[1] == "--planets") && getShipFlag()) {
                setBodyOutput(ship.getNearbyPlanet(planet_system.getPlanetList()));
            }
            else {
                string error =
                    "ERR: Please input a valid flag (try 'scan --help')";
                setErrorOutput(error);
            }
            break;
        case ValidCommand::Sneak:
        {
            if (!getPlanetFlag())
            {
                break;
            }

            playerIsSneaking = true;
            setBodyOutput("You move quietly, preparing a sneak attack...");
            setErrorOutput("");
        }
        break;
        case ValidCommand::Exit:
            setBodyOutput(ship.shipExit());
            setShipFlag(false);
            setPlanetFlag(true);
            break;

        case ValidCommand::ShipMainMenu:
            setBodyOutput(menu.setMenu());
            setMenuFlag(true);
            setShipFlag(false);
            break;

        case ValidCommand::Start:
            setMenuFlag(false);
            setNextFlag(true);
            setBodyOutput(menu.setIntro());
            setArtOutput(art.setArtToAguila());
            planet_system.generatePlanets(20, all_game_rocks);
            break;

        case ValidCommand::Travel:
            try {
                if ((input.size() == 1) ||
                    (input[1] == "-h" || input[1] == "--help")) {
                    setBodyOutput(help.getTravelHelp());
                }
                else if (input[1] == "-d" || input[1] == "--destination") {
                    int index = stoi(input[2]);
                    setBodyOutput(ship.travelToPlanet(index));
                    setArtOutput(getArtForTravelToPlanet(
                        ship.getCurrentPlanet().getBiome(), art));
                }
                else if (input[1] == "-p" || input[1] == "--position") {
                    checkInputSizeLessThanFive(input);
                    array<double, 3> position = {stod(input[2]), stod(input[3]), stod(input[4])};
                    ship.setCoordinates(position);
                    ostringstream output;
                    output << "set coordinates to (" << position[0] << ", "
                        << position[1] << ", " << position[2] << ")";
                    setBodyOutput(output.str());
                }
                else {
                    string error = "ERR: Please pass a valid flag (try 'travel --help')";
                    setErrorOutput(error);
                }
            }
            catch (const invalid_argument& e) {
                string error = "ERR: Invalid argument";
                setErrorOutput(error);
            }
            catch (const out_of_range& e) {
                string error = e.what();
                setErrorOutput(error);
            }
            break;

        case ValidCommand::Talk:
        {
            int npc_index = 0;
            try { npc_index = stoi(input[2]); }
            catch (...) { npc_index = 0; }
            ostringstream output;
            output << ship.getCurrentPlanet().talkToNPC(npc_index) << "\n";

            setBodyOutput(output.str());
        } 
        case ValidCommand::Health:
        {
            string output = "Player health " + to_string(player.getPlayerHealth());
            setErrorOutput(output);
        }
        break;

        default:
            string error = "ERR: Please enter a valid input";
            setErrorOutput(error);
            break;
        }
        if (getPlanetFlag())
        {
            bool countsTowardsAggro = false;

            switch (passed_command)
            {
            case ValidCommand::Collect:
            case ValidCommand::Scan:
            case ValidCommand::Inventory:
            case ValidCommand::Talk:
            case ValidCommand::Health:
                countsTowardsAggro = true;
                break;
            default:
                break;
            }

            if (countsTowardsAggro)
            {
                ++planetCommandCounter;
                if (planetCommandCounter >= MONSTER_ATTACK_THRESHOLD)
                {
                    planetCommandCounter = 0; // reset

                    // Make sure we have a monster for this planet
                    if (!activeMonster)
                    {
                        Planet& active_planet = ship.getCurrentPlanet();
                        Biome biome = active_planet.getBiome();
                        int difficulty = active_planet.getLootLevel();

                        activeMonster = std::make_unique<Monster>(
                            createMonsterForBiomeAndDifficulty(biome, difficulty));
                    }

                    Monster& monster = *activeMonster;

                    if (!monster.isDead())
                    {
                        ostringstream autoMsg;
                        // Keep whatever body text we already had this turn
                        autoMsg << getBodyOutput();
                        if (!getBodyOutput().empty())
                            autoMsg << "\n\n";

                        autoMsg << monster.attackPlayer(player) << "\n"
                            << "(Lingering too long has drawn its attention!)";

                        if (player.isDead())
                        {
                            autoMsg << "\nYou have been slain by "
                                << monster.getName() << "...";
                            setGameOverFlag(true);
                        }

                        setBodyOutput(autoMsg.str());
                    }
                }
            }
        }

        clearScreen(); // Clear screen before start of next loop iteration
    }
}