#include "planet.h"
#include "menu.h"
#include "command.h"
#include "game.h"
// #include "npc.h"

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <sstream>

using namespace std;

// Planet Class Implementation
Planet::Planet(string id, string name, double distanceAU, Biome biome, int loot)
    : id(move(id)), name(move(name)), distanceAU(distanceAU), biome(biome), lootLevel(loot) {
}


double Planet::travelFuelCost(double fuelPerAU) const
{
    return distanceAU * fuelPerAU;
}

string Planet::quickRow(double fuelPerAU) const
{
    ostringstream ss;
    ss << "[" << id << "]" << name
        << " | " << biomeToString(biome)
        << " | " << fixed << setprecision(2) << distanceAU << " AU"
        << " | Fuel Cost: " << travelFuelCost(fuelPerAU);
    return ss.str();
}

string Planet::describe() const
{
    ostringstream ss;
    ss << "\n--- " << name << " ---\n";
    ss << "Biome: " << biomeToString(biome) << "\n";
    ss << "Distance: " << fixed << setprecision(2) << distanceAU << " AU\n";
    ss << "Loot Level: " << lootLevel << "\n";
    ss << "Surface Conditions: "
        << (biome == Biome::Volcanic ? "Molten terrain and unstable geysers."
            : biome == Biome::Ocean ? "Vast seas with strong currents."
            : biome == Biome::Forest ? "Dense vegetation and humid climate."
            : biome == Biome::Urban ? "Ruins of an advanced civilization."
            : biome == Biome::Ice ? "Frozen wastelands under dim sunlight."
            : biome == Biome::Desert ? "Endless dunes and scorching heat."
            : "Barren and lifeless terrain.")
        << "\n";
    return ss.str();
}

string Planet::biomeToString(Biome b)
{
    switch (b)
    {
    case Biome::Desert: return "Desert";
    case Biome::Ice: return "Ice";
    case Biome::Ocean: return "Ocean";
    case Biome::Forest: return "Forest";
    case Biome::Volcanic: return "Volcanic";
    case Biome::GasGiant: return "GasGiant";
    case Biome::Urban: return "Urban";
    case Biome::Barren: return "Barren";
    }
    return "UNKNOWN";
}
PlanetGenerator::PlanetGenerator() : rng(random_device{}()) {}

string PlanetGenerator::generateName()
{
    vector<string> prefixes = { "RX", "M52", "NX", "LX", "KZ", "ULS", "AD" };
    vector<string> suffixes = { "-1b", "-3c", "-Prime", "-Alpha", "-Vega", "-9", "-Tau" };
    uniform_int_distribution<int> num(10, 999);

    string pre = prefixes[rng() % prefixes.size()];
    string suf = suffixes[rng() % suffixes.size()];

    ostringstream name;
    name << pre << "-" << num(rng) << suf;
    return name.str();
}

Planet PlanetGenerator::generatePlanet(int index) {
    uniform_real_distribution<double> distAU(0.5, 10.0);
    double distance = distAU(rng);

    uniform_int_distribution<int> distBiome(0, 7);
    Biome biome = static_cast<Biome>(distBiome(rng));

    uniform_int_distribution<int> distLoot(1, 10);
    int lootLevel = distLoot(rng);

    string name = generateName();
    ostringstream id;
    id << "P" << setw(3) << setfill('0') << index;

    Planet planet(id.str(), name, distance, biome, lootLevel);
    return planet;
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
    /*
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
                        m.MainMenu(cmd, g);
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
            m.MainMenu(cmd, g);
            return;
        }
        else
        {
            g.setErrorOutput("ERR) Invalid input. Type 1, 2, 3, or 'menu'.");
            g.displayOutput();
        }
    }*/
}