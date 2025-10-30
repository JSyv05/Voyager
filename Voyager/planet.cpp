#include "planet.h"
#include "menu.h"
#include "command.h"
#include "game.h"
#include "Rock.h"  
#include <vector>

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <sstream>


using namespace std;

// Rock Implementation
std::vector<Rock> createMasterRockList() {
    std::cout << "Creating master rock list from code..." << std::endl;

    std::vector<Rock> allRocks;

    // Rock(name, description, elementType, value, resourceYielded, yieldAmount)

    allRocks.push_back(Rock(
        "Basalt Shard", "A dark, fine-grained volcanic rock.", "Volcanic",
        10, "Iron", 5
    ));

    allRocks.push_back(Rock(
        "Pumice Stone", "A very light and porous volcanic rock.", "Volcanic",
        5, "Sulfur", 10
    ));

    allRocks.push_back(Rock(
        "Iron Ore", "A rusty-red rock, heavy with metal.", "Metallic",
        25, "Iron", 20
    ));

    allRocks.push_back(Rock(
        "Ice Chunk", "A chunk of frozen, murky water.", "Ice",
        1, "Water", 10
    ));

    allRocks.push_back(Rock(
        "Sandstone", "A common sedimentary rock.", "Desert",
        2, "Silicon", 3
    ));

    allRocks.push_back(Rock(
        "Petrified Wood", "Ancient wood turned to stone.", "Forest",
        15, "Carbon", 10
    ));

    allRocks.push_back(Rock(
        "Barren Stone", "A simple, useless rock.", "Barren",
        0, "Gravel", 1
    ));

    std::cout << "Successfully created " << allRocks.size() << " rocks." << std::endl;
    return allRocks;
}

// Planet Class Implementation
Planet::Planet(string id, string name, double distanceAU, Biome biome, int loot)
    : id_(move(id)), name_(move(name)), distanceAU_(distanceAU), biome_(biome), lootLevel_(loot) {
}

string Planet::quickRow(double fuelPerAU) const
{
    ostringstream ss;
    ss << "[" << id_ << "]" << name_
        << " | " << biomeToString(biome_)
        << " | " << fixed << setprecision(2) << distanceAU_ << " AU"
        << " | Fuel Cost: " << travelFuelCost(fuelPerAU);
    return ss.str();
}

double Planet::travelFuelCost(double fuelPerAU) const
{
    return distanceAU_ * fuelPerAU;
}

string Planet::describe() const
{
    ostringstream ss;
    ss << "\n--- " << name_ << " ---\n";
    ss << "Biome: " << biomeToString(biome_) << "\n";
    ss << "Distance: " << fixed << setprecision(2) << distanceAU_ << " AU\n";
    ss << "Loot Level: " << lootLevel_ << "\n";
    ss << "Surface Conditions: "
        << (biome_ == Biome::Volcanic ? "Molten terrain and unstable geysers."
            : biome_ == Biome::Ocean ? "Vast seas with strong currents."
            : biome_ == Biome::Forest ? "Dense vegetation and humid climate."
            : biome_ == Biome::Urban ? "Ruins of an advanced civilization."
            : biome_ == Biome::Ice ? "Frozen wastelands under dim sunlight."
            : biome_ == Biome::GasGiant ? "Massive storms and crushing pressure."
            : biome_ == Biome::Desert ? "Endless dunes and scorching heat."
            : "Barren and lifeless terrain.")
        << "\n";
    return ss.str();
}

void Planet::populateRocks(const vector<Rock>& allRocksInGame) {
    // Get the planet's biome as a string
    string biomeName = Planet::biomeToString(this->biome_);

    // Clear any old rocks
    this->rocksOnPlanet_.clear();

    // Loop through the master list of all rocks
    for (const Rock& rock : allRocksInGame) {

        // If the rock's type matches the planet's biome, add it
        if (rock.getElementType() == biomeName) {
            this->rocksOnPlanet_.push_back(rock);
        }
    }
}

string Planet::listRocks() const {
    ostringstream ss;
    ss << "\n--- Harvestable Rocks ---\n";
    if (rocksOnPlanet_.empty()) {
        ss << "No harvestable rocks found.\n";
    }
    else {
        for (const Rock& rock : rocksOnPlanet_) {
            // We can't use rock.inspect() because it prints to cout.
            // We'll build the string manually.
            ss << "  - " << rock.getName() << " (" << rock.getElementType() << ")\n";
        }
    }
    return ss.str();
}


// PlanetSystem - Random generation and exploration
void PlanetSystem::run(Game& g)
{
    srand((unsigned)time(nullptr));

    // LOAD ROCKS
    vector<Rock> allGameRocks = createMasterRockList();

    // --- Generate random planets using PlanetGenerator ---
    PlanetGenerator generator;
    vector<Planet> planets;

    const int NUM_PLANETS = 3;
    double fuelPerAU = 2.5;

    for (int i = 0; i < NUM_PLANETS; ++i)
    {
        Planet p = generator.generatePlanet(i + 1);

        p.populateRocks(allGameRocks);

        planets.push_back(std::move(p));
    }

    // --- Display generated planets ---
    ostringstream planetDisplay;
    planetDisplay << "--Nearby Planets Detected--\n";
    for (const auto& p : planets)
        planetDisplay << p.quickRow(fuelPerAU) << "\n";

    planetDisplay << "\n(Type 1, 2, or 3 to travel to a planet, or 'menu' to return to main menu.)";

    g.setTextOutput(planetDisplay.str());
    g.setErrorOutput("");
    g.displayOutput();

    // --- Handle input loop ---
    Command c;
    while (true)
    {
        c.setInput();
        if (c.getInput()->empty()) continue;
        string choice = (*c.getInput())[0];

        if (choice == "1" || choice == "2" || choice == "3")
        {
            int index = stoi(choice) - 1;
            if (index >= 0 && index < (int)planets.size())
            {
                g.clearScreen();
                ostringstream travelMsg;
                travelMsg << "You are now orbiting planet " << planets[index].getName() << ".\n"
                    // << "Fuel Used: " << cost << "\n"
                    // << "Remaining fuel: " << playerFuel << "\n"
                    << planets[index].describe()
                    << planets[index].listRocks()
                    << "\n(Type 'menu' to return to main menu or 'back' to view nearby planets.)";



                g.setTextOutput(travelMsg.str());
                g.setErrorOutput("");
                g.displayOutput();

                // stay on planet until 'back' or 'menu'
                while (true)
                {
                    c.setInput();
                    if (c.getInput()->empty()) continue;
                    string sub = (*c.getInput())[0];

                    if (sub == "menu")
                    {
                        g.clearScreen();
                        Menu m;
                        Command cmd;
                        m.MainMenu(cmd, g);
                        return;
                    }
                    else if (sub == "back")
                    {
                        g.clearScreen();
                        g.setTextOutput(planetDisplay.str());
                        g.setErrorOutput("");
                        g.displayOutput();
                        break;
                    }
                    else
                    {
                        g.setErrorOutput("ERR) Invalid input. Type 'menu' or 'back'.");
                        g.displayOutput();
                    }
                }
            }
        }
        else if (choice == "menu")
        {
            g.clearScreen();
            Menu m;
            Command cmd;
            m.MainMenu(cmd, g);
            return;
        }
        else
        {
            g.setErrorOutput("ERR) Invalid input. Type 1, 2, 3, or 'menu'.");
            g.displayOutput();
        }
    }
}
