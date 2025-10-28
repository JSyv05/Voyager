#ifndef SHIP_H
#define SHIP_H

#include"planet.h"
#include<array>

class Ship {
private:
	std::array<double, 3> coordinates;
public:
	Ship();
    void setCoordinates(const std::array<double, 3>&);
    std::array<double, 3> getCoordinates() const;

	void getNearbyPlanets() const;
    void travelToPlanet() const;
};
#endif
