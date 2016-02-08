#include "../../include/Animation/MovingAnimation.h"

MovingAnimation::MovingAnimation(offset_t _dx, 
								offset_t _dy, 
								delay_t _delay, 
								bool c, 
								animid_t _id) : 
	dx(_dx), 
	dy(_dy), 
	delay(_delay), 
	continuous(c), 
	Animation(_id) {
}

MovingAnimation ::~MovingAnimation() {
	dx = dy = 0;
	delay = -1;
}

void MovingAnimation::setDx(offset_t v) {
	dx = v;
}

offset_t MovingAnimation::getDx(void) const {
	return dx;
}

void MovingAnimation::setDy(offset_t v) {
	dy = v;
}

offset_t MovingAnimation::getDy(void) const {
	return dy;
}

void MovingAnimation::setDelay(delay_t v) {
	delay = v;
}

delay_t MovingAnimation::getDelay(void) const {
	return delay;
}

bool MovingAnimation::getContinuous(void) const {
	return continuous;
}

void MovingAnimation::setContinuous(bool v) {
	continuous = v;
}

Animation* MovingAnimation::clone(animid_t newId) const {
	assert(newId>0);
	return new MovingAnimation(dx, dy, delay, continuous, newId);
}