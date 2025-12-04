#include "art.h"
#include "ship.h"
#include "planet.h"
#include "inventory.h"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

// Constructor
Ship::Ship()
    : coordinates{ 0.0, 0.0, 0.0 },
    previousCoordinates{ 0.0, 0.0, 0.0 },
    currentPlanet("NULL", "EARTH", 0.0, Biome::Barren, 0, { 0,0,0 }),
    radar(3),
    storage(new Inventory(200)) // FIX: Allocate Inventory object on heap
{
}
// Helper functions - Distance and fuel calcutations
static double calcDistanceAU(const array<double, 3>& a, const array<double, 3>& b)
{
    double dx = a[0] - b[0];
    double dy = a[1] - b[1];
    double dz = a[2] - b[2];
    return sqrt(dx * dx + dy * dy + dz * dz) / 10.0; // scale  to AU
}

static double calcFuelCost(double distanceAU, double fuelPerAU)
{
    return distanceAU * fuelPerAU;
}

Inventory* Ship::getShipStorage() {
    return storage;
}

string Ship::getStorageContents() {
    return getShipStorage()->getDisplayString();
}

void Ship::addToShipStorage(Inventory& inventory, int index) {
    Rock temp_rock = inventory.getRockAtIndex(index-1);
    inventory.removeRock(index - 1);
    getShipStorage()->addRock(temp_rock);
}

// Coord setter and getter
void Ship::setCoordinates(const array<double, 3>& coords) {
    coordinates = coords;
}
array<double, 3> Ship::getCoordinates() const { return coordinates; }

// Planet - return handle to the actual planet, so can modify it (e.g. removing rocks)

Planet& Ship::getCurrentPlanet() { return currentPlanet; }

// Radar setter and getter
void Ship::setRadar(int r) { radar = r; }
int Ship::getRadar() const { return radar; }

// Scans for nerby planets
string Ship::getNearbyPlanet(const vector<Planet>& planet_vector) {


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
            << p.quickRow(planetDistances[i].first);
        if (isCurrent)
            display << "  <-- (You Are Here)";
        display << "\n";
    }
    display << "\n(Type 'travel -d 1', 'travel -d 2', or 'travel -d 3' to "
               "visit a planet.)";

    return display.str();

}

// Travel to planet, dock on planet, displays name and description
string Ship::travelToPlanet(int choice) {
    if (choice > 3 || choice < 1) {
        throw out_of_range("ERR: index is out of range");
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

return msg.str();
}

// Return to ship. Plus undock and hover
string Ship::returnToShip() {
    ostringstream msg;
    msg << "You return to your ship and begin pre-flight checks";
    msg << "The ship is now ready for takeoff.\n\n";
    msg << "\n(Type scan -p' to return to scan for nearby planets";

    return msg.str();
}

string Ship::shipExit() {
    ostringstream msg;
    msg << "You step out onto the surface of " << currentPlanet.getName()
        << ".\n\n";
    msg << currentPlanet.describe();
    msg << "\nType 'scan -a' to look around";
    msg << "\n(Type 'return to ship' when you are done";

    return msg.str();
}