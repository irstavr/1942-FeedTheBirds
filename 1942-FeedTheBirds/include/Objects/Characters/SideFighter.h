#ifndef SIDEFIGHTER_H
#define SIDEFIGHTER_H

#include "../../Sprites/Sprite.h"
#include "..\..\Animator\FrameRangeAnimator.h"
#include "..\..\Animation\FrameRangeAnimation.h"
#include "..\..\Animator\AnimatorHolder.h"
#include "..\Items\BirdDropping.h"
#include "..\Items\Fish.h"
#include "./Bird.h"
#include "../../Utilities/Utilities.h"

typedef vector<Fish*> FISHES;

class SideFighter : public Sprite {

private:
	int lives;
	MovingAnimation *appearAnimation, *disappearAnimation;
	MovingAnimator *appearAnimator, *disappearAnimator;
	FISHES *fishes;

public:

	SideFighter(
		Dim _x, Dim _y, 
		AnimationFilm* film,
		MovingAnimation *_appearAnimation,
		MovingAnimator *_appearAnimator,
		MovingAnimation *_disappearAnimation,
		MovingAnimator *_disappearAnimator,
		FISHES *_fishes);

	void move(int dx, int dy);
	void startMoving();
	void stopMoving();
	void disappearSideFighter();

	int getLives();
	void setLives(int n);
	void incrLives();
	void decrLives();

	void die();
	void shoot(vector<Bird*> *birds);
	virtual void collisionAction(Sprite* s);

	void displayAll();
};

#endif
