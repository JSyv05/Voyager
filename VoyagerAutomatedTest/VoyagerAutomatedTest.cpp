#include "pch.h"
#include "CppUnitTest.h"
#include "../Voyager/planet.cpp"
#include "../Voyager/game.cpp"
#include "../Voyager/menu.cpp"
#include "../Voyager/command.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace VoyagerAutomatedTest
{
	TEST_CLASS(VoyagerAutomatedTest)
	{
	public:
		
		TEST_METHOD(Hello_Voyager)
		{
			Logger::WriteMessage("Hello from Dream Team Voyager Test Project\n");
		}

		TEST_METHOD(Planet_Generation)
		{
			Logger::WriteMessage("Testing Planet Generation\n");
			// generate a number of planets & output using planet class describe command
			const int NUM_PLANETS = 5;
			vector <Planet> planets;
			PlanetGenerator generator;

			std::string outputMessage;
			std::string outputMessagePointer;
			outputMessage = "Launching planets " + std::to_string(NUM_PLANETS) + "\n";
			Logger::WriteMessage(outputMessage.c_str());

			for (int planetNum = 0; planetNum < NUM_PLANETS; planetNum++) {
				outputMessage = "\n\nPlanet number " + std::to_string(planetNum) + "\n";
				Logger::WriteMessage(outputMessage.c_str());
				Planet p = generator.generatePlanet(planetNum);
				planets.push_back(p);
				outputMessage = planets[planetNum].describe();
				Logger::WriteMessage(outputMessage.c_str());
			}
		}
	};
}

