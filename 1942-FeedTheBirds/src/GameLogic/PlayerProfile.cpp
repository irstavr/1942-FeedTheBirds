#include <stdio.h>
#include <allegro5/allegro.h>

#include "../../include/GameLogic/PlayerProfile.h"

// constructors
PlayerProfile::PlayerProfile(COORDS xy) {
	score = -1;
	startXY = xy;
	lives = _STARTING_LIFES;
	birdsFeeded = 0;
	hasBonus = false;
	eatenYellowPOW = false;
}

PlayerProfile::PlayerProfile() {
	score = -1;
	startXY = std::make_pair(0, 0);
	lives = _STARTING_LIFES;
	birdsFeeded = 0;
	hasBonus = false;
	eatenYellowPOW = false;
}

// destructor
PlayerProfile::~PlayerProfile() {
	score = -1;
	lives = 0;
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

// score
void PlayerProfile::incrScore(Points addedPoints) {
	assert(addedPoints >= 0);
	score += addedPoints;
}

void PlayerProfile::setScore(Points newScore) { 
	score = newScore; 
}

Points PlayerProfile::getScore(void) { 
	return score; 
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