#ifndef PLANET_H
#define PLANET_H
// Standard C++ libraries
#include <iostream>
#include <sstream>
#include <string>
#include <regex>
#include <vector>
#include <random>
#include <memory>
#include <iomanip>
#include <algorithm>
#include<array>

// User created libraries
#include "game.h"

// Forward declaration of Game
class Game;

using namespace std;

// Biomes
enum class Biome
{
    Desert, Ice, Ocean, Forest, Volcanic, GasGiant, Urban, Barren
};

enum class Size {
    Small, Medium, Large
};

//Planet class
class Planet
{
private:
    string id;
    string name;
    double distanceAU;
    Biome biome;
    int lootLevel;
    vector<float> position;
    array<double, 3> coordinates;

public:
    Planet(string id, string name, double distanceAU, Biome biome, int loot);

    const string& getId() const { return id; }
    const string& getName() const { return name; }
    double getDistanceAU() const { return distanceAU; }
    Biome getBiome() const { return biome; }

    double travelFuelCost(double fuelPerAU) const;



    string quickRow(double fuelPerAU) const;
    string describe() const;

    static string biomeToString(Biome b);
};

// PlanetSysterm will handle displaying and navigating planets
class PlanetSystem
{
public:
    void run(Game& g);
};

//Planet generator
class PlanetGenerator
{
private:
    mt19937 rng;
    string generateName();

public:
    PlanetGenerator();
    Planet generatePlanet(int index);
};
#endif