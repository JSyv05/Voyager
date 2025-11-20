#include "pch.h"
#include "CppUnitTest.h"
#include "../Voyager/Player.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

/*
*  Testing new player class
*/

namespace VoyagerAutomatedTest
{
	TEST_CLASS(PlayerTest)
	{
	public:
		//  Test rock refactoring
		TEST_METHOD(VerifyPlayerCreationWithDefaultHealth) {
			Logger::WriteMessage("Verifying we can create a couple of players with default health\n");
			Player jamesDean;
			Assert::AreEqual(100, jamesDean.getPlayerHealth(), L"expected player health to be 100, but wasn't");
			Logger::WriteMessage("verified that a player was created with 100 health");
		}
	};
}
