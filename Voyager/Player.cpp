#include "Player.h"


/**
 * Player class
 *   Currently only supports creation of player objects with a default health
 * future changes will provide the ability to decrease health.
 */

 // constructor - create a player with initial health
Player::Player() {
	// empty constructor - player health initialized in the header
}


  // returns the current health
int Player::getPlayerHealth() {
	return playerHealth;
}
