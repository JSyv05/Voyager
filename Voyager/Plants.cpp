#include <string>
#include "plants.h"

// Plants class
//   Methods
// 		Constructor - Plants(PLANT_TYPES, std::string plantDescription) - creates a plant of the specified type w/ the specified description
//      string getPlantDescription()  - returns a string with the description provided when the plant was created
//   Enum PLANT_TYPES - lists the available plant types - currently only HYDRANGEAs are supported
//   plantDescription_ - is object storage for the description

Plants::Plants(PLANT_TYPES plantType, std::string plantDescription) {
	plantDescription_ = plantDescription;
	plantType_ = plantType;
}

std::string Plants::getPlantDescription() {
	return plantDescription_;
}
