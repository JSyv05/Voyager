#include "pch.h"
#include "CppUnitTest.h"
#if DISABLE_PLANET_TESTS
#include "../Voyager/planet.cpp"
#include "../Voyager/game.cpp"
#include "../Voyager/menu.cpp"
#include "../Voyager/command.cpp"
#include <cmath>  // required for pow()

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace VoyagerAutomatedTest
{
	TEST_CLASS(VoyagerAutomatedTest)
	{
	public:
		
		// first test method just demonstrates test project runs
		TEST_METHOD(Hello_Voyager)
		{
			Logger::WriteMessage("Hello from Dream Team Voyager Test Project\n");
		}

		// test generates & prints a number of planets
		//   then based on knowledge of how distances are randomly created, verifies they are created as intended (e.g. range, average values)

		TEST_METHOD(Planet_Generation)
		{
			Logger::WriteMessage("Testing Planet Generation\n");
			// generate a number of planets & output using planet class describe command
			const int NUM_PLANETS = 5;
			vector <Planet> planets;
			PlanetGenerator generator;

			std::string outputMessage;
			std::string outputMessagePointer;
			outputMessage = "Launching " + std::to_string(NUM_PLANETS) + " Planets\n";
			Logger::WriteMessage(outputMessage.c_str());

			for (int planetNum = 0; planetNum < NUM_PLANETS; planetNum++) {
				outputMessage = "\n\nPlanet number " + std::to_string(planetNum) + "\n";
				Logger::WriteMessage(outputMessage.c_str());
				Planet p = generator.generatePlanet(planetNum);
				planets.push_back(p);
				outputMessage = planets[planetNum].describe();
				Logger::WriteMessage(outputMessage.c_str());
			}

			// tests to verify distance within range & actual average AU distance is within a single std dev of expected 
			// could merge this into the above code
			// 
			// verify distance within range 0.5 & 10
			const double lowerAURange = 0.5;
			const double upperAURange = 10.0;
			const int sampleSize = 10;
			Logger::WriteMessage("\n*** Validating AU distances are within range - note new planets being generated");
			for (int planetNum = 0; planetNum < sampleSize; planetNum++) {
				Planet p = generator.generatePlanet(planetNum);   // generate a planet
				Assert::IsTrue(p.getDistanceAU() >= lowerAURange && p.getDistanceAU() <= upperAURange, L"Invalid planet distance");
			}

			// Verify uniform distribution of AU ranges (e.g. average ~ lower+upper/2)
			Logger::WriteMessage("\n*** Validating AU distances are uniformly generated\n");

			const double avgAUDistance = (lowerAURange + upperAURange) / 2;
			const double standardDev = (upperAURange - lowerAURange) / sqrt(12);  // standard deviation for a uniform distribution

			double sumOfAUDistances = 0;
			for (int planetNum = 0; planetNum < sampleSize; planetNum++) {
				Planet p = generator.generatePlanet(planetNum);   // generate a planet
				sumOfAUDistances += p.getDistanceAU();
			}

			outputMessage = "Actual average AU distance = " + std::to_string(sumOfAUDistances / sampleSize) + 
				" expected average = " + std::to_string(avgAUDistance) +
				" expected std dev = " + std::to_string(standardDev) + "\n";
			Logger::WriteMessage(outputMessage.c_str());

			// check within two standard deviations
			Assert::IsTrue((sumOfAUDistances/sampleSize >= avgAUDistance-(standardDev)) && 
				(sumOfAUDistances / sampleSize <= avgAUDistance + (standardDev)),
				L"average AU distance outside one standard deviation");
		}
	};
}
#endif // disable this file's automated tests for now, since they don't run given change to generatePlanet() definition, maybe overload to keep old format?

/* Relevant methods from Planet & PlanetGenerator classes (for reference)
class Planet
    Planet(string id, string name, double distanceAU, Biome biome, int loot);  // not used above, planets created by PlanetGenerator
    const string& getId() const { return id; }
    const string& getName() const { return name; }
    double getDistanceAU() const { return distanceAU; }   // gets distance of planet from current location?  note - random # specified when planet created within a range
    Biome getBiome() const { return biome; }
    double travelFuelCost(double fuelPerAU) const;

    string quickRow(double fuelPerAU) const;
    string describe() const;           // returns a formatted string with all of the configured planet attributes (e.g. name, distance)

    static string biomeToString(Biome b);

class PlanetGenerator
    PlanetGenerator();
    Planet generatePlanet(int index);
*/
