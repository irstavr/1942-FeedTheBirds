#ifndef _BIRD_H
#define _BIRD_H

#include "..\Items\BirdDropping.h"
#include "..\..\Animator\FrameRangeAnimator.h"
#include "..\..\Animation\AnimationFilmHolder.h"
#include "..\Items\Fish.h"
#include "..\..\GameAction\CollisionChecker.h"
#include "..\..\GameLogic\PlayerProfile.h"
#include "..\..\GameLogic\ScoreBoard.h"

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
//
// Adds different action speed on every bird
enum BirdSpeed {
	littleBirdSpeed = 10,
	mediumColoredBirdSpeed,
	mediumGreyBirdSpeed,
	ColoredBossSpeed,
	GreyBossSpeed
};

class Bird : public Sprite {
public:
	Bird::Bird(Dim _x, Dim _y,
				BirdID birdID,
				BirdLives birdLives,
				BirdSpeed birdSpeed,
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
	void leaveScreen(void);
	void startMoving(void);
	bool isDead(void);
	void scare();
	int getBirdID();
	virtual void collisionAction(Sprite *s);

private:

	BirdID birdID;
	BirdLives birdLives;
	int birdSpeed;
	bool releasesPowerUp;
	bool isGrey;
	bool isAlive;

	TickAnimation *tickAnimation;
	TimerTickAnimator *timerTick;
};

#endif