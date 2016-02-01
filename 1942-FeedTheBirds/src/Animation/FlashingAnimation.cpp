#include "../../include/Animation/FlashingAnimation.h"

FlashingAnimation::FlashingAnimation(frame_t n, 
									delay_t show, 
									delay_t hide, 
									animid_t id) :
	repetitions(n), 
	hideDelay(hide), 
	showDelay(show), 
	Animation(id) {
}

void FlashingAnimation::setRepetitions(frame_t n) { 
	repetitions = n; 
}

frame_t FlashingAnimation::getRepetitions(void) const { 
	return repetitions; 
}

void FlashingAnimation::setHideDelay(delay_t d) { 
	hideDelay = d; 
}

delay_t FlashingAnimation::getHideDelay(void) const { 
	return hideDelay; 
}

void FlashingAnimation::setShowDelay(delay_t d) { 
	showDelay = d; 
}

delay_t FlashingAnimation::getShowDelay(void) const { 
	return showDelay; 
}

FlashingAnimation* FlashingAnimation::clone(animid_t newId) const {
	return new FlashingAnimation(repetitions, hideDelay, showDelay, newId);
}
