#include "inventory.h"
#include <iostream>
#include <algorithm> 
#include <iomanip>   
#include <sstream>   

// Constructor
Inventory::Inventory(int startCapacity) : maxCapacity(startCapacity) {
}

bool Inventory::addRock(const Rock& rock, std::string& message) {
    if (rocks.size() < maxCapacity) {
        rocks.push_back(rock);
        message = "Added " + rock.getName() + " to inventory.\n(Type 'inventory' to view your inventory)";
        return true;
    }
    else {
        message = "Inventory is full! Cannot add " + rock.getName() + ".";
        return false;
    }
}

bool Inventory::upgradeCapacity(int amount, std::string& message) {
    if (amount > 0) {
        maxCapacity += amount;
        message = "Inventory capacity upgraded by " + std::to_string(amount)
            + "! New capacity: " + std::to_string(maxCapacity);
        return true;
    }
    else {
        message = "Invalid upgrade amount.";
        return false;
    }
}

/**
Helper comparison function for sorting.
 */
bool compareRocksByElement(const Rock& a, const Rock& b) {
    return a.getElementType() < b.getElementType();
}

void Inventory::autoSortRocks() {
    std::sort(rocks.begin(), rocks.end(), compareRocksByElement);
}

std::string Inventory::getDisplayString() const {
    std::ostringstream oss;
    oss << "\n--- INVENTORY (" << rocks.size() << "/" << maxCapacity << ") ---" << std::endl;
    if (rocks.empty()) {
        oss << "Inventory is empty." << std::endl;
        return oss.str();
    }

    const int nameWidth = 20;
    const int typeWidth = 15;
    const int valueWidth = 10;
    const int resourceWidth = 15;

    oss << std::left
        << std::setw(nameWidth) << "Rock Name"
        << std::setw(typeWidth) << "Element"
        << std::setw(valueWidth) << "Value"
        << std::setw(resourceWidth) << "Resource"
        << std::endl;
    oss << std::string(nameWidth + typeWidth + valueWidth + resourceWidth, '-') << std::endl;

    // Use the getter methods from Rock class
    for (const Rock& rock : rocks) {
        oss << std::left
            << std::setw(nameWidth) << rock.getName()
            << std::setw(typeWidth) << rock.getElementType() 
            << std::setw(valueWidth) << rock.getValue()
            << std::setw(resourceWidth) << (std::to_string(rock.getYieldAmount()) + " " + rock.getResourceYielded())
            << std::endl;
    }
    oss << "------------------------------------------------------------\n" << std::endl;
    return oss.str();
}

bool Inventory::removeRock(const std::string& rockName, std::string& message) {
    for (auto it = rocks.begin(); it != rocks.end(); ++it) {
        if (it->getName() == rockName) {
            rocks.erase(it);
            message = "Dropped " + rockName + ".";
            return true;
        }
    }
    message = "ERR: You do not have '" + rockName + "' in your inventory.\n\n";
    return false;
}

std::string Inventory::inspectRock(const std::string& rockName) const {
    for (const Rock& rock : rocks) {
        if (rock.getName() == rockName) {
            std::ostringstream oss;
            oss << "  - " << rock.getName() << " (" << rock.getElementType() << "). Yields "
                << rock.getYieldAmount() << " " << rock.getResourceYielded() << ".";
            return oss.str();
        }
    }
    return "ERR: You do not have '" + rockName + "' in your inventory.\n\n";
}


// --- Getter Implementations ---

int Inventory::getCurrentSize() const {
    return rocks.size();
}

int Inventory::getMaxCapacity() const {
    return maxCapacity;
}