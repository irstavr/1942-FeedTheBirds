#ifndef GAME_PROFILE_H
#define GAME_PROFILE_H

#include "../../include/Utilities/Utilities.h"
#include <stdio.h>
#include <allegro5/allegro.h>
#include <map>

#define _STARTING_LIFES 5

typedef int Points;
typedef int Lives;

class PlayerProfile {

public:
	PlayerProfile();
	~PlayerProfile();

	void incrLives(void);
	void decrLives(void);
	Lives getLives(void);
	bool isDead();

	void setLoops(int n);
	int  getLoops();
	void incrLoops();
	void decrLoops();
	

private:
	COORDS startXY;
	Lives lives;
	int loops;
	bool isAlive;
	unsigned int birdsFeeded;
};

#endif