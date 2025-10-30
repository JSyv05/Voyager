#ifndef PLANET_H
#define PLANET_H
// Standard C++ libraries
#include <iostream>
#include <sstream>
#include <string>
#include <regex>
#include <vector>
#include <random>
#include <memory>
#include <iomanip>
#include <algorithm>

// User created libraries
#include "game.h"
#include "rock.h"

using namespace std;

// Biomes
enum class Biome
{
	Desert, Ice, Ocean, Forest, Volcanic, GasGiant, Urban, Barren
};

// NPC base class and derived types
class NPC
{
protected:
	string name_;
	string description_;

public:
	NPC(string name, string des) : name_(move(name)), description_(move(des)) {}
	virtual ~NPC() = default;

	virtual string getType() const { return "NPC"; }
	virtual void interact() const {
		cout << "You encouter " << name_ << ", " << description_ << "\n";
	}
	const string& getName() const { return name_; }
	const string& getDes() const { return description_; }
};

//Derived classes
class People : public NPC
{
	People(string name, string des) : NPC(move(name), move(des)) {}
	string getType() const override { return "People"; }
	void interact() const override {
		cout << name_ << " greets. " << description_ << "\n";
	}
};

class Monster : public NPC
{
	Monster(string name, string des) : NPC(move(name), move(des)) {}
	string getType() const override { return "Monster"; }
	void interact() const override {
		cout << " A monster appers: " << name_ << "! " << description_ << "\n";
	}
};

class Merchant : public NPC
{
	Merchant(string name, string des) : NPC(move(name), move(des)) {}
	string getType() const override { return "Merchant"; }
	void interact() const override {
		cout << name_ << " opens their shop. " << description_ << "\n";
	}
};

class Event : public NPC
{
	Event(string name, string des) : NPC(move(name), move(des)) {}
	string getType() const override { return "Event"; }
	void interact() const override {
		cout << " Event triggered: " << name_ << " - " << description_ << "\n";
	}
};

//Planet class
class Planet
{
private:
	string id_;
	string name_;
	double distanceAU_;
	Biome biome_;
	int lootLevel_;
	vector<unique_ptr<NPC>> npcs_;  // Each planet's NPCs
	vector<Rock> rocksOnPlanet_; // Rocks available on the planet

public:
	Planet(string id, string name, double distanceAU, Biome biome, int loot);

	const string& getId() const { return id_;  }
	const string& getName() const { return name_; }
	double getDistanceAU() const { return distanceAU_; }
	Biome getBiome() const { return biome_; }

	double travelFuelCost(double fuelPerAU) const;

	

	string quickRow(double fuelPerAU) const;
	string describe() const;

	static string biomeToString(Biome b)
	{
		switch (b)
		{
			case Biome::Desert: return "Desert";
			case Biome::Ice: return "Ice";
			case Biome::Ocean: return "Ocean";
			case Biome::Forest: return "Forest";
			case Biome::Volcanic: return "Volcanic";
			case Biome::GasGiant: return "GasGiant";
			case Biome::Urban: return "Urban";
			case Biome::Barren: return "Barren";
		}
		return "UNKNOWN";
	}

	void addNPC(unique_ptr<NPC> npc)
	{
		npcs_.push_back(move(npc));
	}

	void listNPCs() const
	{
		cout << "\nNPCs on " << name_ << ":\n";
		if (npcs_.empty())
		{
			cout << "None (yet)\n";
			return;
		}
		for (const auto& npc : npcs_)
		{
			cout << "- " << npc->getName() << " (" << npc->getType() << ")\n";
		}
	}

	void interactWithNPCs() const
	{
		if (npcs_.empty())
		{
			cout << "There are no NPCs here.\n";
			return;
		}
		for (const auto& npc : npcs_)
		{
			npc->interact();
		}
	}

	void populateRocks(const vector<Rock>& allRocksInGame); //This will populate Rocks on the planet based on biome

	string listRocks() const; //this is the list of rocks currently on the planet
};

// PlanetSysterm will handle displaying and navigating planets
class PlanetSystem
{
public:
	void run(Game& g);
};

//Planet generator
class PlanetGenerator
{
private:
	mt19937 rng;

	string generateName()
	{
		vector<string> prefixes = { "RX", "M52", "NX", "LX", "KZ", "ULS", "AD" };
		vector<string> suffixes = { "-1b", "-3c", "-Prime", "-Alpha", "-Vega", "-9", "-Tau" };
		uniform_int_distribution<int> num(10, 999);

		string pre = prefixes[rng() % prefixes.size()];
		string suf = suffixes[rng() % suffixes.size()];

		ostringstream name;
		name << pre << "-" << num(rng) << suf;
		return name.str();
	}

public:
	PlanetGenerator() : rng(random_device{}()) {}

	Planet generatePlanet(int index)
	{
		uniform_real_distribution<double> distAU(0.5, 10.0);
		double distance = distAU(rng);

		uniform_int_distribution<int> distBiome(0, 7);
		Biome biome = static_cast<Biome>(distBiome(rng));

		uniform_int_distribution<int> distLoot(1, 10);
		int lootLevel = distLoot(rng);

		string name = generateName();
		ostringstream id;
		id << "P" << setw(3) << setfill('0') << index;

		Planet planet(id.str(), name, distance, biome, lootLevel);

		//Placeholder for NPCs

		return planet;
	}
};
#endif 