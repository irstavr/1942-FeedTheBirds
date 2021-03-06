﻿#include "../../include/Animator/FrameRangeAnimator.h"
#include <iostream>

FrameRangeAnimator::FrameRangeAnimator (void): 
	 	sprite((Sprite*) 0), 
		anim((FrameRangeAnimation*) 0), currFrame(0xFF) {
}

void FrameRangeAnimator::start(Sprite* s, FrameRangeAnimation* a, unsigned long t) {
	sprite = s;
	anim = a;
	lastTime = t;
	state = ANIMATOR_RUNNING;
	sprite->setFrame(currFrame = anim->getStartFrame());
}

Sprite* FrameRangeAnimator::getAnimationSprite() {
	return sprite;
}

frame_t FrameRangeAnimator::getCurrFrame() {
	return currFrame;
}

void FrameRangeAnimator::progress (unsigned long currTime) {

	while (currTime > lastTime && currTime - lastTime >= anim->getDelay()) {
		if (currFrame > anim->getEndFrame())
			currFrame = anim->getStartFrame();
		else {
			sprite->move(anim->getDx(), anim->getDy());
			sprite->setFrame(currFrame);
			lastTime += anim->getDelay();
			++currFrame;

			if (currFrame == anim->getEndFrame() && !anim->getContinuous()) {
				state = ANIMATOR_FINISHED;
				notifyProgressed();
				return;
			}
		}
	}
}

FrameRangeAnimator* FrameRangeAnimator::clone() const {
	return new FrameRangeAnimator();
}

