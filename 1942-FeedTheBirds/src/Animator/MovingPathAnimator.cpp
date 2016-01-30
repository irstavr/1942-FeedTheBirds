#include "..\..\include\Animator\MovingPathAnimator.h"

using namespace std;

MovingPathAnimator::MovingPathAnimator(void) :
	sprite((Sprite*)0),
	anim((MovingPathAnimation*)0), 
	currFrame(0xFF),
	currIndex(0) {
	handleFrames = true;
}

void MovingPathAnimator::start(Sprite* s, MovingPathAnimation* a, unsigned long t) {
	assert(s);
	assert(a);

	sprite = s;
	anim = a;
	lastTime = t;
	state = ANIMATOR_RUNNING;
	currEntry = anim->getFirstPathEntry();
	sprite->setFrame(currFrame = currEntry->frame);
}

MovingPathAnimator * MovingPathAnimator::clone() const
{
	return new MovingPathAnimator();
}

void MovingPathAnimator::setHandleFrames(bool b)
{
	this->handleFrames = b;
}

void MovingPathAnimator::progress(unsigned long currTime) {

	while (currTime > lastTime && currTime - lastTime >= currEntry->delay) {
		sprite->setFlipH(currEntry->h_flip);
		sprite->setFlipV(currEntry->v_flip);
		if(handleFrames) sprite->setFrame(currEntry->frame);
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
