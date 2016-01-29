#ifndef AI_H
#define AI_H

#include "..\Objects\Characters\Bird.h"
#include "..\Objects\Characters\SideFighter.h"
#include "..\Objects\Characters\SuperAce.h"
#include "..\Terrain\Terrain.h"
#include "../GameLogic/GameLogic.h"
#include <sstream>
#include <string>
#include <stdlib.h>
#include <time.h>

#define BASE_ID 10000

class AI {
public:
	AI(GameLogic *_gameLogic, FrameRangeAnimator *_flyAnimator, FrameRangeAnimation *_flyAnimation);
	~AI();

	void eventAtX(int x);


private:
	std::vector<Bird*> *birds;
	std::vector<Bird*> *smallBirds;
	std::vector<Bird*> *mediumBirds;
	std::vector<Bird*> *largeBirds;
	std::vector<Bird*> *bonusBirds;
	FrameRangeAnimation *flyAnimation;
	FrameRangeAnimator *flyAnimator;

	unsigned int lastUsedID;
	GameLogic *gameLogic;

	void addBonusBird(int x, int y);

	void addLittleBird(int x, int y);

	void handleLittleBirds();
	void handleMediumBirds();
	void handleBoss();	
};

#endif