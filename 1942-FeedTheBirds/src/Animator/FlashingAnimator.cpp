#include "../../include/Animator/FlashingAnimator.h"
#include <iostream>

using namespace std;

FlashingAnimator::FlashingAnimator(void) : 
	sprite((Sprite*)0), 
	anim((FlashingAnimation*)0), 
	repetitions(0) {
}

void FlashingAnimator::progress(unsigned long currTime) {
	//fprintf(stdout, "FlashingAnimator progress\n");
	delay_t delay = sprite->isSpriteVisible() ?
					anim->getHideDelay() : anim->getShowDelay();
	bool show = sprite->isSpriteVisible() ? false : true;
	while (currTime > lastTime && currTime - lastTime >= delay) {
		//cout << "repetitions = " << repetitions << "\n";
		sprite->setVisibility(show);
		repetitions++;
		lastTime += delay;
		if ((repetitions == anim->getRepetitions()) && (anim->getRepetitions() != 0)) {
			fprintf(stdout, "stop progress\n");
			state = ANIMATOR_FINISHED;
			sprite->setVisibility(true);
			notifyProgressed();
			repetitions = 0;
			return;
		}
	}
}

void FlashingAnimator::start(Sprite* s, FlashingAnimation* a, unsigned long t) {
	fprintf(stdout, "FlashingAnimator started\n");
	sprite = s;
	anim = a;
	lastTime = t;
	state = ANIMATOR_RUNNING;
}

FlashingAnimator* FlashingAnimator::clone() const {
	return new FlashingAnimator();
}