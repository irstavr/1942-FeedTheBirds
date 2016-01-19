#ifndef _BIRD_H
#define _BIRD_H

#include "..\Items\BirdDropping.h"
#include "..\..\Animator\FrameRangeAnimator.h"
#include "..\..\Animation\AnimationFilmHolder.h"

typedef vector<BirdDropping*> DROPPINGS;

class Bird : public Sprite {
public:
	Bird::Bird(Dim _x, Dim _y, AnimationFilm* film,
		FrameRangeAnimation *_flyAnimation,
		FrameRangeAnimator *_flyAnimator);
	~Bird(void);

	void shoot();
	void displayAll();
	void removeLife(void);
	void leaveScreen(void);
	void startMoving(void);

private:
	int birdLives;
	float birdSpeed;
	bool releasesPowerUp;
	bool isGrey;

	DROPPINGS *droppings;

	FrameRangeAnimation *flyAnimation;
	FrameRangeAnimator *flyAnimator;
	TickAnimation *tickAnimation;
	TimerTickAnimator *timerTick;
};

#endif