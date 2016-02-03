#ifndef AI_H
#define AI_H

#include "..\Objects\Characters\Bird.h"
#include "..\Objects\Characters\SideFighter.h"
#include "..\Objects\Characters\SuperAce.h"
#include "../Animation/MovingPathAnimation.h"
#include "..\Terrain\Terrain.h"
#include "..\GameLogic\GameLogic.h"
#include "..\Utilities\Utilities.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#define BASE_ID 10000
#define PIXELS_PER_SECOND 1000
#define YY (*it)->getY() - gameLogic->superAce->getY()
#define XX (*it)->getX() - (gameLogic->superAce->getX()+200)

//typedef vector<BirdDropping*> DROPPINGS;
class AI {

public:
	AI(GameLogic *_gameLogic, FrameRangeAnimator *_flyAnimator, FrameRangeAnimation *_flyAnimation);
	~AI();

	void eventAtX(int x);

private:
	GameLogic *gameLogic;

	std::vector<Bird*> *bonusBirdsList;
	std::vector<MovingPathAnimator*> *smallBirds;
	std::vector<MovingPathAnimator*> *mediumBirds;
	std::vector<MovingPathAnimator*> *largeBirds;
	std::vector<MovingPathAnimator*> *bonusBirds;

	std::vector<MovingPathAnimator*> *loopers;
	std::vector<MovingAnimator*> *followers;

	FrameRangeAnimation *flyAnimation;
	FrameRangeAnimator *flyAnimator;

	MovingPathAnimator *birdPathAnimator;

	MovingPathAnimation *smallGreenBirdAnimation;
	MovingPathAnimation *smallGreenGreyBirdAnimation;
	MovingPathAnimation *smallGreenBirdAnimationFromAbove;
	MovingPathAnimation *smallBlueBirdAnimation;
	MovingPathAnimation *smallBlueBirdAnimationFromAbove;
	MovingPathAnimation *smallRedBirdAnimation;
	MovingPathAnimation *smallYellowBirdAnimation;
	MovingPathAnimation *smallYellowBirdAnimationFromAbove;
	MovingPathAnimation *smallBlueGreyBirdAnimation;
	MovingPathAnimation *smallYellowGreyBirdAnimation;

	MovingPathAnimation *mediumYellowBirdAnimation;
	MovingPathAnimation *mediumGreenBirdAnimation;
	MovingPathAnimation *mediumBrownBirdAnimation;

	MovingPathAnimation *bigBirdAnimation;

	unsigned int lastUsedID;
	void addBonusBird(int x, int y, char* filmId, MovingPathAnimation* visVitalis);
	void addBonusBirds(void);
	void addSmallBird(int x, int y, char * id, MovingPathAnimation * visVitalis, int followsSuperAce);
	void addSmallBirds();
	void addGreenSmallBird();
	void addBlueSmallBird();
	void addYellowSmallBird();
	void addGreenGreySmallBird();
	void addBlueGreySmallBird();
	void addYellowGreySmallBird();
	void addMediumBirds(void);
	void addMediumBird(int x, int y, char* filmId, BirdLives lives, BirdSpeed speed, MovingPathAnimation* visVitalis, int followsSuperAce);
	void addBoss(int x, int y, char* filmId, BirdLives lives, BirdSpeed speed, MovingPathAnimation* visVitalis);

	void handleLittleBirds();
	void handleMediumBirds();
	void handleBoss();

	void makeBirdFollowSuperAce(Bird *bird, int loops);
	void makeBirdShoot(Bird *bird);

	MovingPathAnimation * createLooperAnimation(int loops);

	Point* getRandomEntryPoint();

	MovingPathAnimation * createBigBirdAnimation();
	MovingPathAnimation * createMediumBrownBirdAnimation();
	MovingPathAnimation * createMediumGreenBirdAnimation();
	MovingPathAnimation * createMediumYellowBirdAnimation();
	MovingPathAnimation * createMediumGreyBirdAnimation();
	MovingPathAnimation * createSmallGreenBirdAnimation();
	MovingPathAnimation * createSmallGreenBirdAnimationFromAbove();
	MovingPathAnimation * createSmallBlueBirdAnimationFromAbove();
	MovingPathAnimation * createSmallYellowBirdAnimationFromAbove();
	MovingPathAnimation * createSmallBlueBirdAnimation();
	MovingPathAnimation * createSmallRedBirdAnimation();
	MovingPathAnimation * createSmallYellowBirdAnimation();
	MovingPathAnimation * createSmallBlueGreyBirdAnimation();
	MovingPathAnimation * createSmallGreenGreyBirdAnimation();
	MovingPathAnimation * createSmallYellowGreyBirdAnimation();
};

#endif

