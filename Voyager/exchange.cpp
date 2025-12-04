#include "exchange.h"
#include "rock.h"

ExchangeStation::ExchangeStation() : lootPoint(0), lootPointToFuel(2), lootPointToHealth(1) {}

int ExchangeStation::getLootPoint() const {
	return lootPoint;
}

void ExchangeStation::addToLootPoint(int x) {
	lootPoint += x;
}

void ExchangeStation::exchangeSampleForLootPoint(Inventory* storage, int index) {
	Rock rock = storage->getRockAtIndex(index-1);
    storage->removeRock(index - 1);
	int lp_to_be_added = rock.getValue();
	addToLootPoint(lp_to_be_added);
}

double ExchangeStation::exchangeLootPointForHealth(int x) {
	if (lootPoint - x < 0) {
		return 0;
	}
	lootPoint -= x;
	return x / lootPointToHealth;
}

double ExchangeStation::exchangeLootPointForFuel(int x) {
	if (lootPoint - x < 0) {
		return 0;
	}
	lootPoint -= x;
	return x / lootPointToFuel;
}