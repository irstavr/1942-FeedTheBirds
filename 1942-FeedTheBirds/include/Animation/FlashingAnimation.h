#ifndef FLASHINGANIMATION_H
#define FLASHINGANIMATION_H

#include "Animation.h"

typedef unsigned char frame_t;

class FlashingAnimation : public Animation {
	frame_t	repetitions;
	delay_t	hideDelay;
	delay_t	showDelay;
public:
	FlashingAnimation(frame_t n, delay_t show, delay_t hide, animid_t id);
	void setRepetitions(frame_t n);
	frame_t getRepetitions(void) const;
	void setHideDelay(delay_t d);
	delay_t getHideDelay(void) const;
	void setShowDelay(delay_t d);
	delay_t getShowDelay(void) const;
	Animation* clone(animid_t newId) const;
};

#endif