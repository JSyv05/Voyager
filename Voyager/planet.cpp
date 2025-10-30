#include "planet.h"
#include "rock.h"
#include "command.h"
#include "game.h"
#include <vector>

#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>


using namespace std;

// Rock Implementation
std::vector<Rock> createMasterRockList() {
    std::cout << "Creating master rock list from code..." << std::endl;

    std::vector<Rock> allRocks;

    // Rock(name, description, elementType, value, resourceYielded, yieldAmount)

    allRocks.push_back(Rock("Basalt Shard",
                            "A dark, fine-grained volcanic rock.", "Volcanic",
                            10, "Iron", 5));

    allRocks.push_back(Rock("Pumice Stone",
                            "A very light and porous volcanic rock.",
                            "Volcanic", 5, "Sulfur", 10));

    allRocks.push_back(Rock("Iron Ore", "A rusty-red rock, heavy with metal.",
                            "Metallic", 25, "Iron", 20));

    allRocks.push_back(Rock("Ice Chunk", "A chunk of frozen, murky water.",
                            "Ice", 1, "Water", 10));

    allRocks.push_back(Rock("Sandstone", "A common sedimentary rock.", "Desert",
                            2, "Silicon", 3));

    allRocks.push_back(Rock("Petrified Wood", "Ancient wood turned to stone.",
                            "Forest", 15, "Carbon", 10));

    allRocks.push_back(Rock("Barren Stone", "A simple, useless rock.", "Barren",
                            0, "Gravel", 1));

    std::cout << "Successfully created " << allRocks.size() << " rocks."
              << std::endl;
    return allRocks;
}

Planet::Planet() = default;

// Planet Class Implementation
Planet::Planet(string id, string name, double distanceAU, Biome biome, int loot)
    : id_(move(id)), name_(move(name)), distanceAU_(distanceAU), biome_(biome),
      lootLevel_(loot) {}

string Planet::quickRow(double fuelPerAU) const {
    ostringstream ss;
    ss << "[" << id_ << "]" << name_ << " | " << biomeToString(biome_) << " | "
       << fixed << setprecision(2) << distanceAU_ << " AU"
       << " | Fuel Cost: " << travelFuelCost(fuelPerAU);
    return ss.str();
}

PlanetGenerator::PlanetGenerator() : rng(std::random_device{}()) {}

double Planet::travelFuelCost(double fuelPerAU) const {
    return distanceAU_ * fuelPerAU;
}

string Planet::describe() const {
    ostringstream ss;
    ss << "\n--- " << name_ << " ---\n";
    ss << "Biome: " << biomeToString(biome_) << "\n";
    ss << "Distance: " << fixed << setprecision(2) << distanceAU_ << " AU\n";
    ss << "Loot Level: " << lootLevel_ << "\n";
    ss << "Surface Conditions: "
       << (biome_ == Biome::Volcanic   ? "Molten terrain and unstable geysers."
           : biome_ == Biome::Ocean    ? "Vast seas with strong currents."
           : biome_ == Biome::Forest   ? "Dense vegetation and humid climate."
           : biome_ == Biome::Urban    ? "Ruins of an advanced civilization."
           : biome_ == Biome::Ice      ? "Frozen wastelands under dim sunlight."
           : biome_ == Biome::GasGiant ? "Massive storms and crushing pressure."
           : biome_ == Biome::Desert   ? "Endless dunes and scorching heat."
                                       : "Barren and lifeless terrain.")
       << "\n";
    return ss.str();
}

void Planet::populateRocks(const vector<Rock>& allRocksInGame) {
    // Get the planet's biome as a string
    string biomeName = Planet::biomeToString(this->biome_);

    // Clear any old rocks
    this->rocksOnPlanet_.clear();

    // Loop through the master list of all rocks
    for (const Rock& rock : allRocksInGame) {

        // If the rock's type matches the planet's biome, add it
        if (rock.getElementType() == biomeName) {
            this->rocksOnPlanet_.push_back(rock);
        }
    }
}

string Planet::biomeToString(Biome b) {
    switch (b) {
    case Biome::Desert:
        return "Desert";
    case Biome::Ice:
        return "Ice";
    case Biome::Ocean:
        return "Ocean";
    case Biome::Forest:
        return "Forest";
    case Biome::Volcanic:
        return "Volcanic";
    case Biome::GasGiant:
        return "GasGiant";
    case Biome::Urban:
        return "Urban";
    case Biome::Barren:
        return "Barren";
    }
    return "UNKNOWN";
}

void Planet::travelToPlanet(Command& command) {
    const auto& input = command.getInput();
    
}

Planet PlanetGenerator::generatePlanet(int index) {
    std::uniform_real_distribution<double> distAU(0.5, 10.0);
    double distance = distAU(rng);

    std::uniform_int_distribution<int> distBiome(0, 7);
    auto biome = static_cast<Biome>(distBiome(rng));

    std::uniform_int_distribution<int> distLoot(1, 10);
    int lootLevel = distLoot(rng);

    std::string name = generateName();
    std::ostringstream id;
    id << "P" << std::setw(3) << std::setfill('0') << index;

    Planet planet(id.str(), name, distance, biome, lootLevel);

    return planet;
}

string PlanetGenerator::generateName()
{ 
            std::vector<std::string> prefixes = {"RX", "M52", "NX", "LX",
                                         "KZ", "ULS", "AD"};
    std::vector<std::string> suffixes = {"-1b",   "-3c", "-Prime", "-Alpha",
                                         "-Vega", "-9",  "-Tau"};
    std::uniform_int_distribution<int> num(10, 999);

    std::string pre = prefixes[rng() % prefixes.size()];
    std::string suf = suffixes[rng() % suffixes.size()];

    std::ostringstream name;
    name << pre << "-" << num(rng) << suf;
    return name.str();
}

string Planet::listRocks() const {
    ostringstream ss;
    ss << "\n--- Harvestable Rocks ---\n";
    if (rocksOnPlanet_.empty()) {
        ss << "No harvestable rocks found.\n";
    }
    else {
        for (const Rock& rock : rocksOnPlanet_) {
            // We can't use rock.inspect() because it prints to cout.
            // We'll build the string manually.
            ss << "  - " << rock.getName() << " (" << rock.getElementType()
               << ")\n";
        }
    }
    return ss.str();
}

vector<Planet> PlanetSystem::getPlanetList() const { return planetList; }
Planet PlanetSystem::getPlanetAtIndex(int index) const{ return planetList[index]; }

// PlanetSystem - Random generation and exploration
void PlanetSystem::run(Game& g) {

    double fuelPerAU = 2.5;

    // --- Display generated planets ---
    ostringstream planetDisplay;
    planetDisplay << "--Nearby Planets Detected--\n";
    for (const auto& p : planetList)
        planetDisplay << p.quickRow(fuelPerAU) << "\n";

    planetDisplay << "\nType 'travel to' followed by the index of the planet to travel there\n\n";

    g.setBodyOutput(planetDisplay.str());
    g.setErrorOutput("");
    g.displayOutput();
}

void PlanetSystem::generatePlanets(int number) {
    PlanetGenerator generator;
    vector<Rock> allGameRocks = createMasterRockList();

    for (int i = 0; i < number; ++i) {
        Planet p = generator.generatePlanet(i + 1);

        p.populateRocks(allGameRocks);

        planetList.push_back(std::move(p));
    }
}