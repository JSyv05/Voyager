#pragma once
class Player
{
private:
	int playerHealth = 100;

public:
	Player();  // constructor - create a player with initial health
	int getPlayerHealth();   // returns the current health
};

