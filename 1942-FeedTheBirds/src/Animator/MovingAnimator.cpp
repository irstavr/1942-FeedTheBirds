#include "..\..\include\Animator\MovingAnimator.h"
#include <assert.h>

MovingAnimator::MovingAnimator(void): 
	sprite((Sprite*)0), 
	anim((MovingAnimation*)0) {
}

MovingAnimator::~MovingAnimator() {

}

MovingAnimation* MovingAnimator::getAnimation(void) {
	return anim;
}

Sprite* MovingAnimator::getSprite(void) {
	return sprite;
}

void MovingAnimator::progress(unsigned long currTime) {
	assert(anim);

	while (currTime > lastTime && currTime - lastTime >= anim->getDelay()) {
		if (!anim->getContinuous()|| sprite->x > SCREEN_WINDOW_WIDTH+150) {
			state = ANIMATOR_FINISHED;
			notifyProgressed();
			return;
		}
		else {
			lastTime += anim->getDelay();
			if (sprite->isSpriteVisible()) {
				sprite->move(anim->getDx(), anim->getDy());
			}
			progress(currTime);
		}
	}
}

void MovingAnimator::start(Sprite* s, MovingAnimation* a, unsigned long t) {
	assert(s);
	assert(a);
	sprite = s;
	anim = a;
	lastTime = t;
	state = ANIMATOR_RUNNING;
}
