#include "pch.h"
#include "CppUnitTest.h"
#include "../Voyager/plants.h"
#include "../Voyager/planet.h"
#include "../Voyager/rock.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace VoyagerAutomatedTest
{
	TEST_CLASS(PlantTest)
	{
	public:
		// first test method just demonstrates test project runs
		TEST_METHOD(Hello_Voyager)
		{
			Logger::WriteMessage("Hello from Plant Test Project\n");
		}
	};
}
