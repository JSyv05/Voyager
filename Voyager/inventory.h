#ifndef INVENTORY_H
#define INVENTORY_H

#include "rock.h" 
#include <vector>
#include <string>

/**
Manages the player's collected rocks.
 */
class Inventory {
private:
    std::vector<Rock> rocks;
    int maxCapacity;

public:
    /**
    Constructor for the Inventory.
     */
    Inventory(int startCapacity);

    /**
    Tries to add a rock to the inventory.
     */
    bool addRock(const Rock& rock, std::string& message);

    /**
    Upgrades the inventory's maximum capacity.
     */
    bool upgradeCapacity(int amount, std::string& message);

    /**
     Sorts the rocks in the inventory by their element type.
     */
    void autoSortRocks();

    /**
    Generates a string representing the inventory's contents.
     */
    std::string getDisplayString() const;

    /**
    Removes a rock from the inventory by name.
     */
    bool removeRock(const std::string& rockName, std::string& message);

    std::string inspectRock(const std::string& rockName) const;


    // --- Getters ---
    int getCurrentSize() const;
    int getMaxCapacity() const;
};

#endif // INVENTORY_H