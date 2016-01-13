#ifndef GAME_PROFILE_H
#define GAME_PROFILE_H

#include "../../include/Utilities/Utilities.h"
#include <map>

typedef unsigned int Lifes;
typedef int Points;

#define _STARTING_LIFES 5

typedef std::pair<bool, bool> PowerUpPair_t;
typedef std::pair<bool, PowerUpPair_t> BlastAnimationMapKey_t;
typedef std::map<BlastAnimationMapKey_t, std::string> BlastAnimationMap_t;

class PlayerProfile {

public:
	PlayerProfile(Lifes startLifes, Coordinates xy);
	PlayerProfile();
	~PlayerProfile();

private:
	BlastAnimationMap_t blastAnimationMap;
	Coordinates startXY;
	Points score;
	Lifes lifes;
	unsigned int birdsFeeded;
	bool hasBonus; //TODO: add every bonus separately !!!
	bool eatenYellowPOW;	//TODO: add every POW here
	bool eatenBlueSPOW;
	bool eatenPurplePOW;

	int getStartX(void);
	int getStartY(void);

	void incrScore(Points addedPoints);
	void setScore(Points newScore);
	Points getScore(void);

	void incrLifes(void);
	void decrLifes(void);
	Lifes getLifes(void);

	void setNumBirdsFeeded(unsigned int birdsNum);
	void incrNumBirdsFeeded(void);
	unsigned int getNumBirdsFeeded(void);



};

#endif