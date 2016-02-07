#include "..\..\..\include\Objects\Items\Fish.h"

Fish::Fish(Dim _x, Dim _y, AnimationFilm* film,
	MovingAnimation *_flyAnimation, MovingAnimator *_flyAnimator) :
	Sprite(_x, _y, film),
	flyAnimation(_flyAnimation),
	flyAnimator(_flyAnimator) {
	isInvisible = false;
	isMetWithBird = false;
	isAlive = true;
}

Fish::~Fish() {
	AnimatorHolder::markAsSuspended(flyAnimator);
	isInvisible = true;
}

bool Fish::inRange(float x, float y, float num) {
	return ((num >= x) && (num <= y));
}

void Fish::move(float dt, float &x, float&y) {
	x += speedX;
}

bool Fish::isDead(void) {
	return !isAlive;
}

void Fish::setDead(void) {
	isAlive = false;
}

void Fish::startMoving(void) {
	flyAnimator->start(this, flyAnimation, getCurrTime());
	AnimatorHolder::markAsRunning(flyAnimator);
}