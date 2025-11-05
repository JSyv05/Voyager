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
    : coordinates{0.0, 0.0, 0.0},
      currentPlanet("NULL", "Unknown", 0.0, Biome::Barren, 0,
                    {0, 0, 0}),               // Placeholder planet
      docked(false), hovering(true), radar(3) // Default scan range
{}

// Coord setter and getter
void Ship::setCoordinates(const array<double, 3>& coords) {
    coordinates = coords;
}
array<double, 3> Ship::getCoordinates() const { return coordinates; }

// Radar setter and getter
void Ship::setRadar(int r) { radar = r; }
int Ship::getRadar() const { return radar; }

// Scans for nerby planets
void Ship::getNearbyPlanet(Game& game) {
    game.clearScreen();

    PlanetSystem system;
    vector<Planet> allPlanets = system.getPlanetList(); // generate 20
    vector<pair<double, Planet>> planetDistances;

    // Calculate distances from ship to each planet
    for (const auto& planet : allPlanets) {
        auto coords =
            planet.getCoordinates(); // Grabs the 3D coords of the planets
        // Calculates the differnce between the ship's and the planet's position
        double dx = coordinates[0] - coords[0];
        double dy = coordinates[1] - coords[1];
        double dz = coordinates[2] - coords[2];
        // The Euclidean distance formula to find how the distance from the
        // planet to the ship in 3D
        double dist = sqrt(dx * dx + dy * dy + dz * dz);

        planetDistances.emplace_back(
            dist, planet); // Stores each planet together with calculated
                           // distance and its name
    }

    // Sort planets by ascending order by distance and begins the closest planet
    sort(planetDistances.begin(), planetDistances.end(),
         [](const auto& a, const auto& b) { return a.first < b.first; });

    lastScannedPlanets.clear();
    for (int i = 0; i < 3 && i < static_cast<int>(planetDistances.size()); ++i)
        lastScannedPlanets.push_back(planetDistances[i].second);

    // Display the closest 3 planets
    ostringstream display;
    display << "--Nearest Planets Detected--\n\n";
    double fuelPerAU = 2.5;
    for (int i = 0; i < static_cast<int>(lastScannedPlanets.size()); ++i)
        display << "(" << (i + 1) << ") "
                << lastScannedPlanets[i].quickRow(fuelPerAU) << "\n";

    display << "\n(Type 'travel to 1', 'travel to 2', or 'travel to 3' to "
               "visit a planet.)";

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

    // Set coords to planet and docks on planet
    currentPlanet = lastScannedPlanets[choice - 1];
    setCoordinates(currentPlanet.getCoordinates());
    docked = true;
    hovering = false;

    ostringstream msg;
    msg << "Docking at " << currentPlanet.getName() << ".\n\n";
    msg << currentPlanet.describe();
    msg << "\nType 'exit ship' to exit to the ship and back into explore the "
           "planet";

    game.clearScreen();
    game.setBodyOutput(msg.str());
    game.setErrorOutput("");
    game.displayOutput();
}

// Return to ship. Plus undock and hover
void Ship::returnToShip(Game& game) {
    // checks if the ship is docked to use them command
    if (!docked) {
        game.setErrorOutput("ERR) You are not docked to any planet.");
        game.displayOutput();
        return;
    }

    // Lift slightly above current planet
    // auto p = currentPlanet.getCoordinates();
    // array<double, 3> hoverCoords = { p[0], p[1] + 10.0, p[2] };
    // setCoordinates(hoverCoords);
    // docked = false;
    // hovering = true;

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
    // checks if the ship is docked to use them command
    if (!docked) {
        game.setErrorOutput("ERR) You are not docked to any planet.");
        game.displayOutput();
        return;
    }

    ostringstream msg;
    msg << "You step out onto the surface of " << currentPlanet.getName()
        << ".\n";
    msg << "The environment is as vast as it is mysterious.\n\n";
    msg << "\n(Type 'return to ship' to enter your ship";

    game.clearScreen();
    game.setBodyOutput(msg.str());
    game.setErrorOutput("");
    game.displayOutput();
}