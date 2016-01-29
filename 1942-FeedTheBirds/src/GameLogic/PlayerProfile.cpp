#include "../../include/GameLogic/PlayerProfile.h"

// constructors
PlayerProfile::PlayerProfile(COORDS xy) {
	startXY = xy;
	lives = _STARTING_LIFES;
	birdsFeeded = 0;
	loops = 3;
	hasBonus = false;
	eatenYellowPOW = false;
}

PlayerProfile::PlayerProfile() {
	startXY = std::make_pair(0, 0);
	lives = _STARTING_LIFES;
	birdsFeeded = 0;
	loops = 3;
	hasBonus = false;
	eatenYellowPOW = false;
}

// destructor
PlayerProfile::~PlayerProfile() {
	lives = 0;
	loops = 0;
	birdsFeeded = 0;
	hasBonus = false;
	eatenYellowPOW = false;
}

int PlayerProfile::getStartX(void) {
	return startXY.first; 
}

int PlayerProfile::getStartY(void) {
	return startXY.second; 
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

// Birds feed
void PlayerProfile::setNumBirdsFeeded(unsigned int birds) { 
	birdsFeeded = birds;
}

void PlayerProfile::incrNumBirdsFeeded(void) { 
	++birdsFeeded;
}

unsigned int PlayerProfile::getNumBirdsFeeded(void) { 
	return birdsFeeded;
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
