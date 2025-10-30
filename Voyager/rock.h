#pragma once

#include <string>
#include <iostream>

class Rock {
public:
    // Constructors
    Rock();
    Rock(const std::string& name, const std::string& description,
        const std::string& elementType, int value,
        const std::string& resourceYielded, int yieldAmount);

    // Public methods
    void inspect() const;

    // Getters
    std::string getElementType() const;
    std::string getName() const;
    int getValue() const;
    std::string getResourceYielded() const;
    int getYieldAmount() const;

private:
    std::string name;
    std::string description;
    std::string elementType;
    int value;
    std::string resourceYielded;
    int yieldAmount;
};
