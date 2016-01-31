#ifndef _BIRD_H
#define _BIRD_H

#include "..\..\Animation\AnimationFilmHolder.h"
#include "..\..\GameAction\CollisionChecker.h"
#include "..\..\Animator\FrameRangeAnimator.h"
#include "..\..\GameLogic\PlayerProfile.h"
#include "..\..\GameLogic\ScoreBoard.h"
#include "..\Items\BirdDropping.h"
#include "..\Items\Fish.h"

typedef vector<BirdDropping*> DROPPINGS;

// used in order to discriminate birds
// and count user's score when feeds them
enum BirdID {
	littleBird = 0,
	mediumBird,
	bossBird
};

// every category of birds has diff num of lives
enum BirdLives {
	littleBirdLives = 1,
	mediumColoredBirdLives = 4,
	mediumGreyBirdLives = 6,
	ColoredBossLives = 25,
	GreyBossLives = 35
};

// TODO: to be used on AI 
// TODO: change values
// Adds different action speed on every bird
enum BirdSpeed {
	littleBirdSpeed = 10,
	mediumColoredBirdSpeed,
	mediumGreyBirdSpeed,
	ColoredBossSpeed,
	GreyBossSpeed
};

enum BirdFire {
	littleBirdFire = 2,
	mediumBirdFire = 8,
	bossBirdFire   = 1000	//endless shooting on the middle of the screen
};

class Bird : public Sprite {

public:
	Bird::Bird(Dim _x, Dim _y,
				BirdID birdID,
				BirdLives birdLives,
				BirdSpeed birdSpeed,
				BirdFire birdFire,
				AnimationFilm* film,
				FrameRangeAnimation *_flyAnimation,
				FrameRangeAnimator *_flyAnimator);
	~Bird(void);
	
	DROPPINGS *droppings;
	BirdDropping* shoot();
	FrameRangeAnimation *flyAnimation;
	FrameRangeAnimator *flyAnimator;

	void displayAll();
	int getLives();
	void removeLife(void);
	void decrFire();
	void leaveScreen(void);
	void startMoving(void);
	bool isDead(void);
	void scare();
	int getBirdID();
	virtual void collisionAction(Sprite *s);

private:
	BirdID birdID;
	BirdLives birdLives;
	BirdSpeed birdSpeed;
	BirdFire birdFire;

	bool releasesPowerUp;
	bool isGrey;
	bool isAlive;

	TickAnimation *tickAnimation;
	TimerTickAnimator *timerTick;
};

#endif