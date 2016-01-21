#ifndef GAME_PROFILE_H
#define GAME_PROFILE_H

#include "../../include/Utilities/Utilities.h"
#include <map>

#define _STARTING_LIFES 5

typedef int Points;
typedef unsigned int Lifes;
typedef std::pair<bool, bool> PowerUpPair_t;
typedef std::pair<bool, PowerUpPair_t> BlastAnimationMapKey_t;
typedef std::map<BlastAnimationMapKey_t, std::string> BlastAnimationMap_t;

class PlayerProfile {

public:
	PlayerProfile(COORDS xy);
	PlayerProfile();
	~PlayerProfile();

	void incrLifes(void);
	void decrLifes(void);
	Lifes getLifes(void);
	bool isDead();
	
	void setNumBirdsFeeded(unsigned int birdsNum);
	void incrNumBirdsFeeded(void);
	unsigned int getNumBirdsFeeded(void);

	int getStartX(void);
	int getStartY(void);

	void incrScore(Points addedPoints);
	void setScore(Points newScore);
	Points getScore(void);

private:
	BlastAnimationMap_t blastAnimationMap;
	COORDS startXY;
	Points score;
	Lifes lifes;
	bool isAlive;
	unsigned int birdsFeeded;
	bool hasBonus; //TODO: add every bonus separately !!!
	bool eatenYellowPOW;	//TODO: add every POW here
	bool eatenBlueSPOW;
	bool eatenPurplePOW;
};

#endif