#ifndef TICKANIMATION_H
#define TICKANIMATION_H
#include <windows.h>
#include "Animation.h"

class TickAnimation : public Animation {
public:
	typedef void(*TickFunc)(void* closure);
private:
	delay_t		delay;
	byte		repetitions;
	TickFunc	action;
	void*		closure;
public:
	TickAnimation(animid_t, delay_t, byte, TickFunc, void*);
	~TickAnimation();

	Animation* clone(animid_t newId) const;
	delay_t getDelay(void) const;
	void setDelay(delay_t v);
	byte getRepetitions(void) const;
	void setRepetitions(byte v);
	void doTickAction(void);
	void setTickAction(TickFunc, void*);
};

#endif