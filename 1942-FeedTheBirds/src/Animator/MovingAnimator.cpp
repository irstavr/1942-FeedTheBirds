#include "..\..\include\Animator\MovingAnimator.h"
#include <assert.h>

MovingAnimator::MovingAnimator(void): 
	sprite((Sprite*)0), 
	anim((MovingAnimation*)0) {
}

MovingAnimator :: ~MovingAnimator() {
}

MovingAnimation* MovingAnimator::getAnimation(void) {
	return anim;
}

Sprite* MovingAnimator::getSprite(void) {
	return sprite;
}

void MovingAnimator::progress(unsigned long currTime) {
	assert(currTime >= 0);
	assert(anim);
	assert(lastTime <= currTime);

	while (currTime > lastTime && currTime - lastTime >= anim->getDelay()) {
		//sprite->move(anim->getDx(), anim->getDy());
		// or
		sprite->move(anim->getDx(), anim->getDy());
		//sprite->setFlipH(anim->getFlipH());
		//sprite->setFlipV(anim->getFlipV()); 
		if (!anim->getContinuous()) {
			state = ANIMATOR_FINISHED;
			notifyProgressed();
			return;
		}
		else
			lastTime += anim->getDelay();
			progress(currTime);  // Recursion (make it a loop)
	}

}

void MovingAnimator::start(Sprite* s, MovingAnimation* a, unsigned long t) {
	assert(s);
	assert(a);
	assert(t >= 0);
	sprite = s;
	anim = a;
	lastTime = t;
	state = ANIMATOR_RUNNING;
}

void MovingAnimator::display(ALLEGRO_BITMAP* at) {
	sprite->display(at);
}