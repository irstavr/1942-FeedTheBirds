#ifndef MOVINGANIMATION_H
#define MOVINGANIMATION_H

#include "Animation.h"

class MovingAnimation : public Animation {
	offset_t dx, dy;
	delay_t	delay;
	bool continuous;

public:
	MovingAnimation(offset_t _dx, offset_t _dy, delay_t _delay, bool c, animid_t _id);
	~MovingAnimation();

	offset_t getDx(void) const;
	void setDx(offset_t v);
	offset_t getDy(void) const;
	void setDy(offset_t v);
	delay_t getDelay(void) const;
	void setDelay(delay_t v);
	bool getContinuous(void) const;
	void setContinuous(bool v);
	Animation* clone(animid_t newId) const;
};

#endif