#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <vector>
#include "..\Sprites\PlaneSprite.h"

//typedef vector<BirdSprite*> BIRDS;

class GameLogic {
	//SuperAceSprite *myPlane;
	//BIRDS &birds;
	int height, width, planeKilled;
	bool gameRunning;
	//float calcDis(COORDS a, COORDS b);

public:
	//GameLogic(SuperAceSprite *ac, BIRDS &ep, int h, int w);
	/*solve all the outrange stuff*/
	void solveOutRange();
	/*solve all the collision stuff*/
	int solveCollision(int &p, int status);
	/*decide if add bird*/
	bool addBird(float &t, int p);
	/*return if the game is still running*/
	bool isRunning() const;
};

#endif