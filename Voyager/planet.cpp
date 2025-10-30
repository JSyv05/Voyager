#include "planet.h"
#include "menu.h"
#include "command.h"
#include "game.h"

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <cmath>

using namespace std;

// Planet Class Implementation
// Default constructor 
Planet::Planet() : id("NULL"), name("Unkown"), distanceAU(0.0), biome(Biome::Barren), lootLevel(0), coordinates({ 0.0,0.0,0.0 }) {}

// Constructor initializes all planet properties
Planet::Planet(string id, string name, double distanceAU, Biome biome, int loot, array<double, 3> coords)
    : id(move(id)), name(move(name)), distanceAU(distanceAU), biome(biome), lootLevel(loot), coordinates(coords) {}

// Getter Implementations
const string& Planet::getId() const { return id; }
const string& Planet::getName() const { return name; }
double Planet::getDistanceAU() const { return distanceAU; }
Biome Planet::getBiome() const { return biome; }
array<double, 3> Planet::getCoordinates() const { return coordinates; }

// Calculates the fuel cost to travel
double Planet::travelFuelCost(double fuelPerAU) const
{
    return distanceAU * fuelPerAU;
}

// Returns a sumary line for the planet list
string Planet::quickRow(double fuelPerAU) const
{
    ostringstream ss;
    ss << "[" << id << "]" << name
        << " | " << biomeToString(biome)
        << " | " << fixed << setprecision(2) << distanceAU << " AU"
        << " | Fuel Cost: " << travelFuelCost(fuelPerAU);
    return ss.str();
}

// Returns a describe of the planet
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

// Converts enum Biome to string for display
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

// PlanetGenerator Implementation 
PlanetGenerator::PlanetGenerator() : rng(random_device{}()) {}

// Randomly creates a planet name
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

// Create a planet with random attributes and unqiue coordinates
Planet PlanetGenerator::generatePlanet(int index, const vector<array<double, 3>>& existingCoords) 
{
    uniform_real_distribution<double> distAU(0.5, 10.0);
    double distance = distAU(rng);

    uniform_int_distribution<int> distBiome(0, 7);
    Biome biome = static_cast<Biome>(distBiome(rng));

    uniform_int_distribution<int> distLoot(1, 10);
    int lootLevel = distLoot(rng);

    uniform_real_distribution<double> distCoord(-50.0, 50.0);

    // Ensure coordinate are unique
    array<double, 3> coords;
    bool unique = false;
    while (!unique)
    {
        coords = { distCoord(rng), distCoord(rng), distCoord(rng) };
        unique = true;

        for (const auto& c : existingCoords)
        {
            double dx = coords[0] - c[0];
            double dy = coords[1] - c[1];
            double dz = coords[2] - c[2];
            double dist = sqrt(dx * dx + dy * dy + dz * dz);
            if (dist < 5.0)
            {
                unique = false;
                break;
            }
        }

    }
    // Create a name and ID
    string name = generateName();
    ostringstream id;
    id << "P" << setw(3) << setfill('0') << index;

    return { id.str(), name, distance, biome, lootLevel, coords };
}

// PlanetSystem - Random generation and exploration
vector<Planet> PlanetSystem::run()
{
    srand((unsigned)time(nullptr));

    //  Generate random planets using PlanetGenerator 
    PlanetGenerator generator;
    vector<Planet> planets;
    vector<array<double, 3>> usedCoords; //store coordinates to make sure they are unique

    const int NUM_PLANETS = 20;

    // Generate 20 unique planets
    for (int i = 0; i < NUM_PLANETS; ++i)
    {
        Planet p = generator.generatePlanet(i + 1, usedCoords);
        usedCoords.push_back(p.getCoordinates());
        planets.push_back(move(p));
    }

    return planets;
}