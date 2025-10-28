#include "ship.h"
#include "planet.h"

#include<cmath>

using namespace std;

Ship::Ship() : coordinates{0.0, 0.0, 0.0} {};

void Ship::setCoordinates(const array<double, 3>& coords) {
    coordinates = coords;
}

array<double, 3> Ship::getCoordinates() const { return coordinates; }

void Ship::getNearbyPlanets() const{

}

void Ship::travelToPlanet() const{

}