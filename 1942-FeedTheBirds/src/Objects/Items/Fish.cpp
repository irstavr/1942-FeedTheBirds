#include "..\..\..\include\Objects\Items\Fish.h"

// TODO: if bonuses change bullets
// add another field for advancing speed
Fish::Fish(Dim _x, Dim _y, AnimationFilm* film,
	MovingAnimation *_flyAnimation, MovingAnimator *_flyAnimator) :
	Sprite(_x, _y, film),
	flyAnimation(_flyAnimation),
	flyAnimator(_flyAnimator) {
	isInvisible = false;
	isMetWithBird = false;
}

Fish::~Fish()
{
	isInvisible = true;
	isMetWithBird = false;
}

bool Fish::inRange(float x, float y, float num) {
	return ((num >= x) && (num <= y));
}

void Fish::move(float dt, float &x, float&y) {
	x += speedX;// *dt;
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