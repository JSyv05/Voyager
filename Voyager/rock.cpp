#include "Rock.h"
#include <iostream>

// Default constructor implementation
Rock::Rock() : id(0), researchValue(0) {}

// Updated constructor implementation
Rock::Rock(int id, std::string name, std::string desc, int value, std::string rarity)
    : id(id), name(name), description(desc), researchValue(value), rarity(rarity) {}

// displayInfo function implementation (no changes here)
void Rock::displayInfo() const {
    std::cout << "  - ID: " << id << std::endl;
    std::cout << "    Name: " << name << " (" << rarity << ")" << std::endl;
    std::cout << "    Value: " << researchValue << " Research Points" << std::endl;
    std::cout << "    Desc: " << description << std::endl;
}
