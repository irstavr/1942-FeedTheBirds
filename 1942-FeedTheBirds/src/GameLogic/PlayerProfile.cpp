#include "../../include/GameLogic/PlayerProfile.h"

// constructors
PlayerProfile::PlayerProfile() {
	startXY = std::make_pair(0, 0);
	lives = _STARTING_LIFES;
	birdsFeeded = 0;
	loops = 3;
}

// destructor
PlayerProfile::~PlayerProfile() {
	lives = 0;
	loops = 0;
	birdsFeeded = 0;
}

// lifes
void PlayerProfile::incrLives(void) { 
	++lives;
}

void PlayerProfile::decrLives(void) { 
	--lives;
}

Lives PlayerProfile::getLives(void) { 
	return lives; 
}

bool PlayerProfile::isDead() {
	if (lives == 0) {
		return true;
	}
	return false;
}

void PlayerProfile::setLoops(int n)
{
	this->loops = n;
}

int PlayerProfile::getLoops()
{
	return this->loops;
}

void PlayerProfile::incrLoops()
{
	this->loops++;
}

void PlayerProfile::decrLoops()
{
	this->loops--;
}
