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
	FrameRangeAnimation *takeOffAnimation, *landAnimation, *deathAnimation;
	FrameRangeAnimator *takeOffAnimator, *landAnimator, *deathAnimator;
	FISHES *fishes;

public:

	SideFighter(
		Dim _x, Dim _y, 
		AnimationFilm* film,
		FrameRangeAnimation *_takeOffAnimation, 
		FrameRangeAnimator *_takeOffAnimator,
		FrameRangeAnimation *_landAnimation,
		FrameRangeAnimator *_landAnimator,
		FrameRangeAnimation *_deathAnimation,
		FrameRangeAnimator *_deathAnimator, 
		FISHES *_fishes);


	void move(int dx, int dy);
	void startMoving();

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
