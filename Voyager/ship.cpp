#include "ship.h"
#include "game.h"
#include "planet.h"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <sstream>

using namespace std;

// Constructor
Ship::Ship()
    : coordinates{ 0.0, 0.0, 0.0 },
    currentPlanet("NULL", "EARTH", 0.0, Biome::Barren, 0, { 0,0,0 }),
    radar(3),
    previousCoordinates{ 0.0, 0.0, 0.0 } // if still declared
{}
// Helper functions - Distance and fuel calcutations
static double calcDistanceAU(const array<double, 3>& a, const array<double, 3>& b)
{
    double dx = a[0] - b[0], dy = a[1] - b[1], dz = a[2] - b[2];
    return sqrt(dx * dx + dy * dy + dz * dz) / 10.0; // scale to AU
}

static double calcFuelCost(double distanceAU, double fuelPerAU)
{
    return distanceAU * fuelPerAU;
}

// Coord setter and getter
void Ship::setCoordinates(const array<double, 3>& coords) {
    coordinates = coords;
}
array<double, 3> Ship::getCoordinates() const { return coordinates; }

// Radar setter and getter
void Ship::setRadar(int r) { radar = r; }
int Ship::getRadar() const { return radar; }

// Scans for nerby planets
void Ship::getNearbyPlanet(Game& game, const vector<Planet>& planet_vector) {
    game.clearScreen();

    const double fuelPerAU = 2.5;
    vector<pair<double, Planet>> planetDistances;

   // Calcute all distances once
    for (const auto& p : planet_vector) 
    {
        double dAU = calcDistanceAU(coordinates, p.getCoordinates());
        planetDistances.push_back({ dAU, p });
    }

    // Sort planets by ascending distance
    sort(planetDistances.begin(), planetDistances.end(),
        [](const auto& a, const auto& b) { return a.first < b.first; });

    lastScannedPlanets.clear();

    // Add the 3 closest planets
    int count = min(radar, (int)planetDistances.size());
    for (int i = 0; i < count; ++i)
    {
        lastScannedPlanets.push_back(planetDistances[i].second);
    }

    // Include current planet after first travel
    bool hasTraveledBefore = (currentPlanet.getName() != "EARTH");
    if (hasTraveledBefore) { lastScannedPlanets.push_back(currentPlanet); }

    // Display
    ostringstream display;
    display << "--Nearest Planets Detected--\n\n";
    for (int i = 0; i < count; ++i) {
        const Planet& p = planetDistances[i].second;
        double fuelCost = calcFuelCost(planetDistances[i].first, fuelPerAU);
        bool isCurrent = (p.getName() == currentPlanet.getName());

        display << "(" << (i + 1) << ") "
            << p.quickRow(planetDistances[i].first, fuelCost);
        if (isCurrent)
            display << "  <-- (You Are Here)";
        display << "\n";
    }

    game.setBodyOutput(display.str());
    game.setErrorOutput("");
    game.displayOutput();

    // Update state flags
    game.setShipFlag(true);
    game.setPlanetFlag(false);
}

// Travel to planet, dock on planet, displays name and description
void Ship::travelToPlanet(Game& game, int choice) {
    if (lastScannedPlanets.empty()) {
        game.setErrorOutput("ERR: No planets scanned. Use 'scan' first.\n");
        game.displayOutput();
        return;
    }

    Planet destination = lastScannedPlanets[choice - 1];
    const auto& destCoords = destination.getCoordinates();

    // Calculate travel stats
    double distanceAU = calcDistanceAU(coordinates, destCoords);
    double fuelPerAU = 2.5;
    double fuelCost = calcFuelCost(distanceAU, fuelPerAU);

    previousCoordinates = coordinates;
    coordinates = destCoords;
    currentPlanet = destination;

    ostringstream msg;
    msg << "Traveling to " << currentPlanet.getName() << "...\n";
    msg << "Distance: " << std::fixed << std::setprecision(2) << distanceAU << " AU\n";
    msg << "Fuel Used: " << fuelCost << "\n\n";
    msg << "Docking at " << currentPlanet.getName() << ".\n";
    msg << currentPlanet.describe();
    msg << "\n(Type 'exit ship' to step out onto the surface.)";

    game.clearScreen();
    game.setBodyOutput(msg.str());
    game.setErrorOutput("");
    game.displayOutput();
}

// Return to ship. Plus undock and hover
void Ship::returnToShip(Game& game) {
    ostringstream msg;
    msg << "You return to your ship and begin pre-flight checks";
    msg << "The ship is now ready for takeoff.\n\n";
    msg << "\n(Type scan' to return to scan for nearby planets";

    game.clearScreen();
    game.setBodyOutput(msg.str());
    game.setErrorOutput("");
    game.displayOutput();
}

void Ship::shipExit(Game& game) {
    ostringstream msg;
    msg << "You step out onto the surface of " << currentPlanet.getName()
        << ".\n";
    msg << "The environment is as vast as it is mysterious.\n\n";
    //msg << "\n(Type 'return to ship' to enter your ship";

    game.clearScreen();
    game.setBodyOutput(msg.str());
    game.setErrorOutput("");
    game.displayOutput();
}