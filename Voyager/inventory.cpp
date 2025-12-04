#include "inventory.h"
#include <iostream>
#include <algorithm> 
#include <iomanip>   
#include <sstream>   
#include <string>

using namespace std;

// Constructor
Inventory::Inventory(int startCapacity) : maxCapacity(startCapacity) {
}

bool Inventory::addRock(const Rock& rock) {
    if (rocks.size() < maxCapacity) {
        rocks.push_back(rock);
        return true;
    }
    else {
        return false;
    }
}

bool Inventory::upgradeCapacity(int amount, string& message) {
    if (amount > 0) {
        maxCapacity += amount;
        message = "Inventory capacity upgraded by " + to_string(amount)
            + "! New capacity: " + to_string(maxCapacity);
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
    sort(rocks.begin(), rocks.end(), compareRocksByElement);
}

string Inventory::getDisplayString() const {
    ostringstream oss;
    oss << "\n--- INVENTORY (" << rocks.size() << "/" << maxCapacity << ") ---" << endl;
    if (rocks.empty()) {
        oss << "Inventory is empty." << endl;
        return oss.str();
    }

    const int nameWidth = 20;
    const int typeWidth = 15;
    const int valueWidth = 10;
    const int resourceWidth = 15;

    oss << left
        << setw(nameWidth) << "Rock Name"
        << setw(typeWidth) << "Element"
        << setw(valueWidth) << "Value"
        << setw(resourceWidth) << "Resource"
        << endl;
    oss << string(nameWidth + typeWidth + valueWidth + resourceWidth, '-') << endl;

    // Use the getter methods from Rock class
    for (const Rock& rock : rocks) {
        oss << left
            << setw(nameWidth) << rock.getName()
            << setw(typeWidth) << rock.getElementType() 
            << setw(valueWidth) << rock.getValue()
            << setw(resourceWidth) << (to_string(rock.getYieldAmount()) + " " + rock.getResourceYielded())
            << endl;
    }
    oss << "------------------------------------------------------------\n" << endl;
    return oss.str();
}

Rock Inventory::getRockAtIndex(int index) {
    return rocks[index];
}

string Inventory::removeRock(const int& index) {
    ostringstream oss;
    try {
        if (index - 1 < 0 || index > rocks.size()) {
            throw out_of_range("ERR: please input a valid index for the inventory system");
        }
        Rock rock = getRockAtIndex(index - 1);
        rocks.erase(rocks.begin() + index - 1);
        oss << "Removed " << rock.getName();
        return oss.str();
    }
    catch (const out_of_range& e) {
        oss << e.what();
        return oss.str(); 
    }    
}

string Inventory::inspectRock(const int& index) {

    ostringstream oss;
    try {
        if (index - 1 < 0 || index > rocks.size()) {
            throw out_of_range("ERR: please input a valid index for the inventory system");
        }
        Rock rock = getRockAtIndex(index - 1);
        rocks.erase(rocks.begin() + index - 1);
        oss << "  - " << rock.getName() << " (" << rock.getElementType() << "). Yields "
            << rock.getYieldAmount() << " " << rock.getResourceYielded() << ".";
        return oss.str();
    }
    catch (const out_of_range& e) {
        oss << e.what();
        return oss.str();
    }
}


// --- Getter Implementations ---

int Inventory::getCurrentSize() const {
    return static_cast<int>(rocks.size());
}

int Inventory::getMaxCapacity() const {
    return maxCapacity;
}