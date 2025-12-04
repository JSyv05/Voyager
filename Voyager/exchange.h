#ifndef EXCHANGE_H
#define EXCHANGE_H

#include "inventory.h"

/*
The exchange station is where you can trade ion the samples that you have collected for a currency syste called Loot Points.
You can use these Loot Points to refuel your ship or to restore your health.
*/

class ExchangeStation {
private:
	int lootPoint;
	double lootPointToFuel;
	double lootPointToHealth;
public:
	ExchangeStation();
	int getLootPoint() const;
	void addToLootPoint(int);
	void subtractFromLootPoint(int);
	void exchangeSampleForLootPoint(Inventory*, int);
	double exchangeLootPointForFuel(int);
	double exchangeLootPointForHealth(int);
};
#endif
