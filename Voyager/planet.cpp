#include "planet.h"
#include "menu.h"
#include "command.h"
#include "game.h"

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <sstream>

using namespace std;

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

// PlanetSystem - Random generation and exploration
void PlanetSystem::run(Game& g)
{
    srand((unsigned)time(nullptr));

    // --- Generate random planets using PlanetGenerator ---
    PlanetGenerator generator;
    vector<Planet> planets;

    const int NUM_PLANETS = 3;
    double fuelPerAU = 2.5;

    for (int i = 0; i < NUM_PLANETS; ++i)
    {
        Planet p = generator.generatePlanet(i + 1);
        planets.push_back(std::move(p));
    }

    // --- Display generated planets ---
    ostringstream planetDisplay;
    planetDisplay << "--Nearby Planets Detected--\n";
    for (const auto& p : planets)
        planetDisplay << p.quickRow(fuelPerAU) << "\n";

    planetDisplay << "\n(Type 1, 2, or 3 to travel to a planet, or 'menu' to return to main menu.)";

    g.setBodyOutput(planetDisplay.str());
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
                    << "\n(Type 'menu' to return to main menu or 'back' to view nearby planets.)";

                g.setBodyOutput(travelMsg.str());
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
                        return;
                    }
                    else if (sub == "back")
                    {
                        g.clearScreen();
                        g.setBodyOutput(planetDisplay.str());
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
            return;
        }
        else
        {
            g.setErrorOutput("ERR) Invalid input. Type 1, 2, 3, or 'menu'.");
            g.displayOutput();
        }
    }
}
