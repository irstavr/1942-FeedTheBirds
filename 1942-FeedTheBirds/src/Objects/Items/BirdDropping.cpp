#include "..\..\..\include\Objects\Items\BirdDropping.h"

BirdDropping::BirdDropping(Dim _x, Dim _y, AnimationFilm* film,
	MovingAnimation *_flyAnimation, MovingAnimator *_flyAnimator) :
	Sprite(_x, _y, film),
	flyAnimation(_flyAnimation),
	flyAnimator(_flyAnimator) {
	isInvisible = false;
	isMetWithBird = false;
}

BirdDropping::~BirdDropping()
{
	delete flyAnimation;
	delete flyAnimator;
	delete tickAnimation;
	delete timerTick;
}

bool BirdDropping::inRange(float x, float y, float num) {
	return ((num >= x) && (num <= y));
}

void BirdDropping::move(float dt, float &x, float&y) {
	x += speedX;
}

void BirdDropping::startMoving(void) {
	flyAnimator->start(this, flyAnimation, getCurrTime());
	AnimatorHolder::markAsRunning(flyAnimator);
}