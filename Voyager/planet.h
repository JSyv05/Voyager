#ifndef PLANET_H
#define PLANET_H
// Standard C++ libraries
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <memory>
#include <random>
#include <sstream>
#include <string>
#include <vector>
#include <array>

// User created libraries
#include "game.h"
#include "rock.h"

// Biomes
enum class Biome { Desert, Ice, Ocean, Forest, Volcanic, GasGiant, Urban, Barren };

// Planet size
enum class Size { Small, Medium, Large };

//Planet class
class Planet
{
private:
    string id;
    string name;
    double distanceAU;
    Biome biome;
    int lootLevel;
    array<double, 3> coordinates;

public:
    // Constructor
    Planet();
    Planet(string id, string name, double distanceAU, Biome biome, int loot, array<double, 3> coords);

    // Getters
    const string& getId() const; 
    const string& getName() const;
    double getDistanceAU() const;
    Biome getBiome() const;
    array<double, 3> getCoordinates() const;

    // Core methods
    double travelFuelCost(double fuelPerAU) const;
    string quickRow(double fuelPerAU) const;
    string describe() const;

    std::string listRocks() const; // this is the list of rocks currently on the planet
};

//Planet generator
class PlanetGenerator
{
private:
    mt19937 rng; // Random number generator
    string generateName();

public:
    PlanetGenerator();
    Planet generatePlanet(int index, const vector<array<double, 3>>& existingCoords);
};

// PlanetSysterm will handle displaying and navigating planets
class PlanetSystem
{
public:
    vector<Planet> run();
};

#endif