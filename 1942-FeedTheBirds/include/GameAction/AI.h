#ifndef AI_H
#define AI_H

#include "..\Objects\Characters\Bird.h"
#include "..\Objects\Characters\SideFighter.h"
#include "..\Objects\Characters\SuperAce.h"
#include "../Animation/MovingPathAnimation.h"
#include "..\Terrain\Terrain.h"
#include "..\GameLogic\GameLogic.h"
#include "..\Utilities\Utilities.h"
#include <sstream>
#include <string>
#include <stdlib.h>
#include <cmath>
#include <time.h>

#define BASE_ID 10000
#define PIXELS_PER_SECOND 1000
#define YY (*it)->getY() - gameLogic->superAce->getY()
#define XX (*it)->getX() - (gameLogic->superAce->getX()+200)
#define PI 3.14159
#define XforCircle(radius) sin(i*PI / 180)*radius 
#define YforCircle(radius) cos(i*PI / 180)*radius

class AI {

public:
	AI(GameLogic *_gameLogic, FrameRangeAnimator *_flyAnimator, FrameRangeAnimation *_flyAnimation);
	~AI();

	void eventAtX(int x);
	void startTakingOff();

private:
	GameLogic *gameLogic;

	std::vector<Bird*> *birds;
	std::vector<MovingPathAnimator*> *smallBirds;
	std::vector<Bird*> *mediumBirds;
	std::vector<Bird*> *largeBirds;
	std::vector<Bird*> *bonusBirds;

	FrameRangeAnimation *flyAnimation;
	FrameRangeAnimator *flyAnimator;
	MovingPathAnimation *smallGreenBirdAnimation;
	MovingPathAnimator *smallGreenBirdAnimator;

	unsigned int lastUsedID;

	void addBonusBird(int x, int y);
	void addLittleBird(int x, int y);

	void handleLittleBirds();
	void handleMediumBirds();
	void handleBoss();
	MovingPathAnimation * createSmallGreenBirdAnimation();
	std::list<PathEntry>* createSmoothDiagonalPath(int dx, int dy);
	std::list<PathEntry>* createCircularPath(int radius, int startAngle, int endAngle);
};

#endif

