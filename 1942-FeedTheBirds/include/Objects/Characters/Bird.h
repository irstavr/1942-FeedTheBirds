#ifndef _BIRD_H
#define _BIRD_H

#include "..\Items\BirdDropping.h"
#include ".\SuperAce.h"
#include "..\..\Animator\FrameRangeAnimator.h"
#include "..\..\Animation\AnimationFilm.h"
#include "..\..\GameAction\CollisionChecker.h"

typedef vector<BirdDropping*> DROPPINGS;

class Bird : public Sprite {
public:
	Bird::Bird(Dim _x, Dim _y, AnimationFilm* film,
				FrameRangeAnimation *_flyAnimation,
				FrameRangeAnimator *_flyAnimator);
	~Bird(void);
	
	DROPPINGS *droppings;

	void shoot(CollisionChecker*& checker, SuperAce* &superAce);
	void displayAll();
	int getLives();
	void removeLife(void);
	void leaveScreen(void);
	void startMoving(void);
	void createRoute(void);
	bool isDead(void);

	FrameRangeAnimation *flyAnimation;
	FrameRangeAnimator *flyAnimator;

	virtual void collisionAction();
	//virtual void collisionAction(Sprite *s);
private:

	int birdLives;
	float birdSpeed;
	bool releasesPowerUp;
	bool isGrey;

	bool isAlive;

	TickAnimation *tickAnimation;
	TimerTickAnimator *timerTick;
};

#endif