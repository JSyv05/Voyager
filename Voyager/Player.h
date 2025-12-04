#pragma once
class Player
{
private:
	int playerHealth = 100;

public:
	Player();  // constructor - create a player with initial health
	int getPlayerHealth();   // returns the current health

	//Combat
	int dealDamage() const;
	void takeDamage(int dmg);
	bool isDead() const;
	void attackMonster(class Monster& monster) const;
};

