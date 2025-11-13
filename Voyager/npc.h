#pragma once
#include <string>
#include <vector>

using namespace std;

// Forward declaration from planet.h
enum class Biome;

// Types of NPCs
enum class NpcCategory { Person, Monster, Merchant, Event };

// NPC structure
class NPC
{
private:
    string name_;
    string openingLine_;
    string appearance_;
    NpcCategory category_;
    Biome biome_;

public:
    NPC() = default;
    NPC(string name, string line, string appearance, NpcCategory cat, Biome biome);

    string getType() const;
    string getName() const;
    string getOpeningLine() const;
    string getAppearance() const;
    Biome getBiome() const;

    string shortCard(int index) const;
    string talkText() const;
};

// Returns all NPCs in the game
const vector<NPC>& getAllNPCs();

// Picks N NPCs by biome (no repeats)
vector<NPC> pickNPCsForBiome(Biome biome, int count);