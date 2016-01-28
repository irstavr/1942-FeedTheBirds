#include "..\..\include\Animator\MovingPathAnimator.h"

using namespace std;

MovingPathAnimator::MovingPathAnimator(void) :
	sprite((Sprite*)0),
	anim((MovingPathAnimation*)0), 
	currFrame(0xFF),
	currIndex(0) {
}

void MovingPathAnimator::start(Sprite* s, MovingPathAnimation* a, unsigned long t) {
	cout << __FUNCTION__ << "\n";
	assert(s);
	assert(a);

	sprite = s;
	anim = a;
	lastTime = t;
	state = ANIMATOR_RUNNING;
	currEntry = anim->getFirstPathEntry();
	sprite->setFrame(currFrame = currEntry->frame);
}

void MovingPathAnimator::progress(unsigned long currTime) {
	cout << __FUNCTION__ << "\n";

	while (currTime > lastTime && currTime - lastTime >= currEntry->delay) {
		//sprite->move(currEntry->dx, currEntry->dy);
		sprite->setFlipH(currEntry->h_flip);
		sprite->setFlipV(currEntry->v_flip);
		sprite->setFrame(currEntry->frame);
		sprite->move(currEntry->dx, currEntry->dy);
		lastTime += currEntry->delay;
		++currEntry;
		if (currEntry == anim->getLastPathEntry()) {
			state = ANIMATOR_FINISHED;
			currEntry = anim->getFirstPathEntry();
			notifyProgressed();
			return;
		}

	}
}
