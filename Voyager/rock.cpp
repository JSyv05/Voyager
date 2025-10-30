#include "Rock.h"
#include <iostream>

// Constructors 
Rock::Rock()
    : name("Unnamed Rock"), description("Just a rock."),
    elementType("Generic"), value(0),
    resourceYielded("Gravel"), yieldAmount(1) {
}

Rock::Rock(const std::string& name, const std::string& description,
    const std::string& elementType, int value,
    const std::string& resourceYielded, int yieldAmount)
    : name(name), description(description), elementType(elementType),
    value(value), resourceYielded(resourceYielded), yieldAmount(yieldAmount) {
}

// Public Methods
void Rock::inspect() const {
    std::cout << "  - " << name << " (" << elementType << "). Yields "
        << yieldAmount << " " << resourceYielded << "." << std::endl;
}

// Getters
std::string Rock::getElementType() const { return elementType; }
std::string Rock::getName() const { return name; }
int Rock::getValue() const { return value; }
std::string Rock::getResourceYielded() const { return resourceYielded; }
int Rock::getYieldAmount() const { return yieldAmount; }
