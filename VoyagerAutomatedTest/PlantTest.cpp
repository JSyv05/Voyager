#include "pch.h"
#include "CppUnitTest.h"
#include "../Voyager/plants.h"
#include "../Voyager/planet.h"
#include "../Voyager/rock.h"
#include "../Voyager/npc.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

/* 
*  Plants (aka flora) functionality test cases
*  more details to come once we populate the plants.h header file
*/

namespace VoyagerAutomatedTest
{
	TEST_CLASS(PlantTest)
	{
	public:
		// first test method just demonstrates test project runs
		TEST_METHOD(Hello_PlantTest)
		{
			Logger::WriteMessage("Hello from Plant Test Project\n");
		}

		// create a few plant types & verify created correctly
		TEST_METHOD(Create_Plants) {
			Logger::WriteMessage("Creating a few plants & verifying created correctly and accessible\n");
			std::string pinkHydrangeaDescription = "a lovely pink hydrangea";
			Plants pink(Plants::HYDRANGEA, pinkHydrangeaDescription);
			Assert::AreEqual(pinkHydrangeaDescription, pink.displayPlantDescription());
			Logger::WriteMessage("passed pinkHydrangeaDescription test\n");

			std::string blueHydrangeaDescription = "a striking blue hydrangea";
			Plants blue(Plants::HYDRANGEA, blueHydrangeaDescription);
			Assert::AreEqual(blueHydrangeaDescription, blue.displayPlantDescription());
			Logger::WriteMessage("passed blueHydrangeaDescription test\n");
		}

		// next create some planets - but this needs us to generate the next set of code changes
		TEST_METHOD(Create_Planets) {
			Logger::WriteMessage("Creating a few planets & verify the flora is created correctly\n");
			Planet planetArray[5];
			PlanetGenerator generator;
			//     Planet(std::string id, std::string name, double distanceAU, Biome biome,int loot, std::array<double, 3>)
			// Planet PlanetGenerator::generatePlanet(int index, const vector<array<double, 3>>& existingCoords) {
			// verify that I can create 5 forest planets & will see 5 an hydrangea on each planet
			for (int planetNum = 0; planetNum < 5; planetNum++) {
				planetArray[planetNum] = generator.generatePlanet(planetNum, { {0,0}, {0,0}, {0,0} });
				std::string s = planetArray[planetNum].listPlantsOnPlanet();
				Logger::WriteMessage(s.c_str());
			}
		}
	};
}
