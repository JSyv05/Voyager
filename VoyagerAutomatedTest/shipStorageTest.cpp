#include "pch.h"
#include "CppUnitTest.h"
#include "../Voyager/ship.h"
#include "../Voyager/inventory.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace VoyagerautomatedTest {
    TEST_CLASS(ShipStorageTest){
        TEST_METHOD(list_storage){
            Logger::WriteMessage("Testing to see if the ship will list out it's contents");
            Ship ship;
            string not_expected = "";
            string expected = ship.getShipStorage();
            Assert::IsTrue(not_expected != expected, L"ERR: List did not print properly");
        }
        TEST_METHOD(move_from_inventory_to_storage) {
            Logger::WriteMessage("Testing to move from one rock from inventory to storage");
        }
    };
}