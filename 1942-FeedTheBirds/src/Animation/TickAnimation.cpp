#include "../../include/Animation/TickAnimation.h"

TickAnimation::TickAnimation(animid_t _id, delay_t	_delay, byte _repetitions, TickFunc _action, void* _closure) :
	delay(_delay), repetitions(_repetitions), action(_action), closure(_closure), Animation(_id) {
}

TickAnimation::~TickAnimation() {
	delay = 0;
	repetitions = 0;
	action = 0;
	closure = 0;
}

void TickAnimation::doTickAction(void) {
	if (action)
		(*action)(closure);
}

void TickAnimation::setTickAction(TickFunc	_action, void* _closure) {
	action = _action;
	closure = _closure;
}

Animation* TickAnimation::clone(animid_t newId) const {
	return new TickAnimation(newId, delay, repetitions, action, closure);
}

delay_t TickAnimation::getDelay(void) const {
	return delay;
}

void TickAnimation::setDelay(delay_t v) {
	delay = v;
}

byte TickAnimation::getRepetitions(void) const {
	return repetitions;
}

void TickAnimation::setRepetitions(byte v) {
	repetitions = v;
}
