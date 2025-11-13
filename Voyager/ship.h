#ifndef SHIP_H
#define SHIP_H

#include"art.h"
#include "planet.h"
#include <array>
#include <vector>

using namespace std;
class Game; // forward declaration

class Ship {
private:
    array<double, 3> coordinates;      // Ship coordinates
    vector<Planet> lastScannedPlanets; // The 3 closest planets after scanning.
                                       // Later the ship can
    Planet currentPlanet;              // The planet the ship at
    bool docked;
    bool hovering;
    int radar; // Number of planets from scan (default is 3)

public:
    Ship();

    // Planet

    Planet getCurrentPlanet() const;

    // Coordinates
    void setCoordinates(const array<double, 3>& coords);
    array<double, 3> getCoordinates() const;

    // Radar
    void setRadar(int r);
    int getRadar() const;

    // Ship actions
    void getNearbyPlanet(Game& game,const std::vector<Planet>&);            // Scans for planets
    void travelToPlanet(Game& game, int choice, Art&); // Travel/Dock at chosen planet
    void returnToShip(Game& game);               // Returns tp ship
    void shipExit(Game& game);                   // Exits ship
};
#endif