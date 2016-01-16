#include "..\..\..\include\Objects\Characters\SuperAce.h"

SuperAce::SuperAce(Dim _x, Dim _y, AnimationFilm* film,
	FrameRangeAnimation *_takeOffAnimation, 
	FrameRangeAnimator *_takeOffAnimator,
	FrameRangeAnimation *_landAnimation, 
	FrameRangeAnimator *_landAnimator,
	FrameRangeAnimation *_deathAnimation, 
	FrameRangeAnimator *_deathAnimator) :
	Sprite(_x, _y, film),
	takeOffAnimation(_takeOffAnimation), 
	takeOffAnimator(_takeOffAnimator),
	landAnimation(_landAnimation), 
	landAnimator(_landAnimator),
	deathAnimation(_deathAnimation), 
	deathAnimator(_deathAnimator) {
	isInvisible = false;
	isShooting = false;
}

SuperAce::~SuperAce(void) {

}

void SuperAce::moveUp() {

}

void SuperAce::moveDown() {

}

void SuperAce::moveLeft() {

}

void SuperAce::moveRight() {
	
}