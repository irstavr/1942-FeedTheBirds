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
#include <algorithm>
#include <string>
#include <cstdlib>
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

	MovingPathAnimator *birdPathAnimator;
	MovingPathAnimation *smallGreenBirdAnimation;
	MovingPathAnimation *smallBlueBirdAnimation;
	MovingPathAnimation *smallRedBirdAnimation;
	MovingPathAnimation *smallYellowBirdAnimation;

	unsigned int lastUsedID;

	void addSmallBird(int x, int y, char * id, MovingPathAnimation * visVitalis);

	void handleLittleBirds();
	void handleMediumBirds();
	void handleBoss();
	MovingPathAnimation * createbigBirdAnimation();
	MovingPathAnimation * createMediumBrownBirdAnimation();
	MovingPathAnimation * createMediumGreenBirdAnimation();
	MovingPathAnimation * createMediumYellowBirdAnimation();
	MovingPathAnimation * createSmallGreenBirdAnimation();
	MovingPathAnimation * createSmallBlueBirdAnimation();
	MovingPathAnimation * createSmallRedBirdAnimation();
	MovingPathAnimation * createSmallYellowBirdAnimation();
	std::list<PathEntry>* createSmoothDiagonalPath(int dx, int dy);
	std::list<PathEntry>* createCircularPath(int radius, int startAngle, int endAngle);
};

#endif

