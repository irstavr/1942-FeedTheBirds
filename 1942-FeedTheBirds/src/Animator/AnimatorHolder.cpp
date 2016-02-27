#include "../../include/Animator/AnimatorHolder.h"

std::list<Animator*> AnimatorHolder::running;
std::list<Animator*> AnimatorHolder::suspended;
std::list<Animator*> AnimatorHolder::paused;

unsigned long AnimatorHolder::pauseTime;

void AnimatorHolder::animRegister(Animator* a) {
	assert(a);
	suspended.push_back(a);
}

void AnimatorHolder::cancel(Animator* a) {
	suspended.remove(a);
}

void AnimatorHolder::markAsRunning(Animator* a) {
	suspended.remove(a);
	running.push_back(a);
}

void AnimatorHolder::markAsSuspended(Animator* a) {
	running.remove(a);
	suspended.push_back(a);
}


void AnimatorHolder::progress(unsigned long currTime) {
	std::for_each(running.begin(), running.end(), ProgressFunctor(currTime));
}

void AnimatorHolder::pause() {
	pauseTime = clock();

	std::list<Animator *>::iterator it;

	for (it = running.begin(); it != running.end(); ++it) {
		 paused.push_back(*it);
	}
	running.clear();
}

void AnimatorHolder::pauseAllExcept(Animator* anim) {
	pauseTime = clock();

	std::list<Animator *>::iterator it;

	for (it = running.begin(); it != running.end(); ++it) {
			if (*it != anim) paused.push_back(*it);
	}
	running.clear();
	running.push_back(anim);
}

void AnimatorHolder::resume(void) {
	unsigned long pauseOffset = (clock() - pauseTime);

	std::list<Animator*>::iterator it;
	for (it = paused.begin(); it != paused.end(); ++it) {
		(*it)->timeShift(pauseOffset);
		running.push_back(*it);
	}
	paused.clear();
}