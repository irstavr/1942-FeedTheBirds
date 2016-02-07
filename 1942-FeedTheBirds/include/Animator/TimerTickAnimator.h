#ifndef TIMERTICKANIMATOR_H
#define TIMERTICKANIMATOR_H

#include "Animator.h"
#include "..\Animation\TickAnimation.h"

#include <iostream>

class TimerTickAnimator : public Animator {

private:
	TickAnimation*	tick;
	byte			repetitions;
public:
	explicit TimerTickAnimator(TickAnimation* _tick);
	~TimerTickAnimator(void);

	TickAnimation* getAnimation(void);
	void start(unsigned long time);
	void progress(unsigned long currTime);
};

#endif