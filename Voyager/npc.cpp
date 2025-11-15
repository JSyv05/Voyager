#include "npc.h"
#include "planet.h"
#include <algorithm>
#include <random>

using namespace std;

// NPC Implementation
NPC::NPC(string name, string line, string appearance, NpcCategory cat, Biome biome)
    : name_(move(name)), openingLine_(move(line)), appearance_(move(appearance)), category_(cat), biome_(biome) {
}

string NPC::getType() const
{
    switch (category_)
    {
    case NpcCategory::Person: return "Person";
    case NpcCategory::Monster: return "Monster";
    case NpcCategory::Merchant: return "Merchant";
    case NpcCategory::Event: return "Event";
    default: return "Unknown";
    }
}

string NPC::getName() const { return name_; }
string NPC::getOpeningLine() const { return openingLine_; }
string NPC::getAppearance() const { return appearance_; }
Biome NPC::getBiome() const { return biome_; }

string NPC::shortCard(int index) const
{
    return "(" + to_string(index) + ") " + name_ + " | " + getType();
}

string NPC::talkText() const
{
    return name_ + " says: " + openingLine_ + "\nAppearance: " + appearance_ + "\n";
}

// NPC DATA (2 per Biome for testing)
static vector<NPC> ALL_NPCS =
{
    // Forest
    {"Gorm Garnersson",
     "Greetings outlander, I am Gorm of house Garnersson. What brings you to this realm?",
     "7.5 ft tall, draconic features, armored knight with sword and dagger.",
     NpcCategory::Person, Biome::Forest},
    {"Woodrow Burch",
     "Don’t go barking up the wrong tree, pal.",
     "Tree-guy with green leafy hair.",
     NpcCategory::Person, Biome::Forest},

     // Volcanic
     {"Hot Mama",
      "Is it gettin’ hot in here or is it just you?",
      "Long flowing flame hair; eyes like burning coals.",
      NpcCategory::Person, Biome::Volcanic},
     {"Haot Roks",
      "Roks.",
      "8-ft volcanic rock being with glowing cracks.",
      NpcCategory::Monster, Biome::Volcanic},

      // Ocean
      {"Whaley Mamaley",
       "Butter my blowhole, ain’t you a sight for sore eyes!",
       "Whale in overalls with a top hat.",
       NpcCategory::Person, Biome::Ocean},
      {"Marina May",
       "Warm waves welcome you, traveler.",
       "Coral body with pink-to-orange gradient.",
       NpcCategory::Merchant, Biome::Ocean},

       // Ice
       {"Icicle",
        "I control the snow, ice, and cold.",
        "Blue skin, white hair, blue leather jumpsuit.",
        NpcCategory::Person, Biome::Ice},
       {"Shivers McTimber",
        "There be a cold wind hoistin’ me sails.",
        "Pirate — but blue because he’s cold.",
        NpcCategory::Person, Biome::Ice},

        // Gas Giant
        {"Stormie Nitez",
         "A storm’s a brewin’.",
         "Dark cloud-like hair with lightning streaks.",
         NpcCategory::Event, Biome::GasGiant},
        {"Feebus Fellow",
         "Who the hell are you?",
         "5’2, pink hair, surprisingly nice clothes.",
         NpcCategory::Person, Biome::GasGiant},

         // Barren
         {"P.A.R.E.",
          "... SCANNING ... USER NOT FOUND ... SHOW DRESCO ID.",
          "Rusty humanoid robot barely moving.",
          NpcCategory::Merchant, Biome::Barren},
         {"Barren John",
          "OoooOooOoOoOoOoOoOoOoo...",
          "Dark silhouette with glowing eyes.",
          NpcCategory::Event, Biome::Barren},

          // Urban
          {"Taxi Jaxi",
           "Need yaself a ride? Take a ride in Taxi Jaxi’s Jaxi Taxi!",
           "1920s-style cabbie with newsboy hat.",
           NpcCategory::Merchant, Biome::Urban},
          {"Justin Case",
           "Greetings partner… foremost, amazing, genius, expert…",
           "5'8 robot in dirty overcoat; cardboard badge.",
           NpcCategory::Person, Biome::Urban},

           // Desert
           {"Dusty Oasis",
            "Awful hot out there — rest in the shade.",
            "Desert gear; sandy hair with blue streaks.",
            NpcCategory::Person, Biome::Desert},
           {"Jane Finch",
            "Jane Finch. I'm a problem solver.",
            "Cowgirl engineer with belts full of gadgets.",
            NpcCategory::Person, Biome::Desert},
};

const vector<NPC>& getAllNPCs() { return ALL_NPCS; }

vector<NPC> pickNPCsForBiome(Biome biome, int count)
{
    vector<NPC> pool;
    for (auto& npc : ALL_NPCS)
        if (npc.getBiome() == biome)
            pool.push_back(npc);

    if (pool.empty())
        return {};

    static mt19937 rng{ random_device{}() };
    shuffle(pool.begin(), pool.end(), rng);

    if ((int)pool.size() > count)
        pool.resize(count);

    return pool;
}