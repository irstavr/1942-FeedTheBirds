#ifndef _BIRD_H
#define _BIRD_H

#include "..\Items\BirdDropping.h"
#include "..\..\Animator\FrameRangeAnimator.h"
#include "..\..\Animation\AnimationFilmHolder.h"
#include "..\Items\Fish.h"
#include "..\..\GameAction\CollisionChecker.h"
//#include "SuperAce.h"

typedef vector<BirdDropping*> DROPPINGS;

class Bird : public Sprite {
public:
	Bird::Bird(Dim _x, Dim _y, AnimationFilm* film,
				FrameRangeAnimation *_flyAnimation,
				FrameRangeAnimator *_flyAnimator);
	~Bird(void);
	
	DROPPINGS *droppings;

//	void shoot(CollisionChecker*& checker, SuperAce* &superAce);
	void displayAll();
	void removeLife(void);
	void leaveScreen(void);
	void startMoving(void);
	void createRoute();
	FrameRangeAnimation *flyAnimation;
	FrameRangeAnimator *flyAnimator;

	virtual void collisionAction(Sprite *s);
private:

	int birdLives;
	float birdSpeed;
	bool releasesPowerUp;
	bool isGrey;

	TickAnimation *tickAnimation;
	TimerTickAnimator *timerTick;
};

#endif