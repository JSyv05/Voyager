#pragma once
#include <string>

class Rock {
public:
    // Attributes of a rock
    int id;
    std::string name;
    std::string description;
    int researchValue;
    std::string rarity;

    // Default constructor
    Rock();

    // Constructor to easily create a new rock
    Rock(int id, std::string name, std::string desc, int value, std::string rarity);

    // A function to display the rock's details
    void displayInfo() const;
};
