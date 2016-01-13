#include "../../include/Animator/TimerTickAnimator.h"

TimerTickAnimator::TimerTickAnimator(TickAnimation* _tick) :
	tick(_tick), 
	repetitions(0) {
}

TimerTickAnimator::~TimerTickAnimator(void) {
}

TickAnimation* TimerTickAnimator::getAnimation(void) {
	return tick;
}

void TimerTickAnimator::start(unsigned long time) {
	assert(time >= 0);
	fprintf(stdout, "tickTimer started\n");
	lastTime = time;
	state = ANIMATOR_RUNNING;
}

void TimerTickAnimator::progress(unsigned long currTime) {
	assert(tick);
	assert(lastTime <= currTime);

	while (currTime > lastTime && 
		   currTime - lastTime >= tick->getDelay()) {

		tick->doTickAction();
		lastTime += tick->getDelay();
		++repetitions;
		if ((repetitions == tick->getRepetitions()) &&
		   (tick->getRepetitions() != 0) ) {
			state = ANIMATOR_FINISHED;
			notifyProgressed();
			return;
		}
	}
}