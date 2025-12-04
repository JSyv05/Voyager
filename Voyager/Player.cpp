#include "Player.h"
#include "npc.h"

// Forward declaration
class monster;

/**
 * Player class
 *   Currently only supports creation of player objects with a default health
 * future changes will provide the ability to decrease health.
 */

 // constructor - create a player with initial health
Player::Player() {
	// empty constructor - player health initialized in the header
}
//add two method 
//bool iscrritable
//method to decrease

//gameloop just checks

  // returns the current health
int Player::getPlayerHealth() 
{
	return playerHealth;
}

int Player::dealDamage() const
{
	return 10;   //Hard code value we can change this later. needed to test the monster taking damage
}
 

void Player::takeDamage(int dmg)
{
	playerHealth -= dmg;
	if (playerHealth < 0)
		playerHealth = 0;
}

bool Player::isDead() const
{
	return playerHealth <= 0;
}

void Player::attackMonster(Monster& monster) const
{
	int dmg = dealDamage(); 
	monster.takeDamage(dmg);
}