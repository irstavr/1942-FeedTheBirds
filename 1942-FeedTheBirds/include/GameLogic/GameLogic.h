#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <vector>
#include "..\Sprites\Sprite.h"
#include "..\Objects\Characters\SuperAce.h"
#include "..\Objects\Characters\Bird.h"

typedef vector<Bird*> BIRDS;

class GameLogic {
	SuperAce *superAce;
	BIRDS &birds;
	int height, width, planeKilled;
	bool gameRunning;
	float calcDis(COORDS a, COORDS b);

public:
	GameLogic(SuperAce *superAce, BIRDS &birds, int height, int width);
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