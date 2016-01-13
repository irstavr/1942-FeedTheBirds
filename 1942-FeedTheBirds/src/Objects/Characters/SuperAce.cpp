#include "..\..\..\include\Objects\Characters\SuperAce.h"

SuperAce::SuperAce(Dim _x, Dim _y, AnimationFilm* film,
	MovingAnimation *_takeOffAnimation, MovingAnimator *_takeOffAnimator,
	MovingAnimation *_landAnimation, MovingAnimator *_landAnimator,
	MovingAnimation *_deathAnimation, MovingAnimator *_deathAnimator) :
	Sprite(_x, _y, film),
	landAnimation(_landAnimation), landAnimator(_landAnimator),
	deathAnimation(_deathAnimation), deathAnimator(_deathAnimator) {
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