#pragma once
#include <string>

class Plants
{
        // from design subtask
		// Methods:
		//   constructor Plants(enum plantName, string plantDescription)
		//    ToDo - possibly add planet name in future
		//  string displayPlantDescription()
		//Data structures :
		//   enum plantNameEnum  (changing to PLANT_TYPES)
		//   string plantDescription
public:
		enum PLANT_TYPES { HYDRANGEA }; // only define a single plant for now, choosing Upper Snake Case as contrast to command enum definition

		Plants(PLANT_TYPES, std::string plantDescription);
		std::string displayPlantDescription();

private:
	std::string plantDescription_;
	PLANT_TYPES plantType_;
};
