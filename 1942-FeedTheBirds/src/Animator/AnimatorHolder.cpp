#include "../../include/Animator/AnimatorHolder.h"


std::vector<Animator*> AnimatorHolder::running, AnimatorHolder::suspended;
std::vector<Animator*> AnimatorHolder::paused;
unsigned long AnimatorHolder::pauseTime;

void AnimatorHolder::animRegister(Animator* a) {
	assert(a);
	suspended.push_back(a);
}

void AnimatorHolder::cancel(Animator* a) {
	assert(!suspended.empty());
	assert(a);

	std::vector<Animator*>::iterator it = std::find(suspended.begin(), suspended.end(), a);
	assert(it != suspended.end());
	suspended.erase(it);
}

void AnimatorHolder::markAsRunning(Animator* a) {
	assert(!suspended.empty());
	assert(a);
	std::vector<Animator*>::iterator it = std::find(suspended.begin(), suspended.end(), a);
	assert(it != suspended.end());
	suspended.erase(it);
	running.push_back(a);
}

void AnimatorHolder::markAsSuspended(Animator* a) {
	assert(!running.empty());
	assert(a);

	std::vector<Animator*>::iterator it = std::find(running.begin(), running.end(), a);
	assert(it != running.end());
	running.erase(it);
	suspended.push_back(a);
}

void AnimatorHolder::progress(unsigned long currTime) {
	assert(currTime >= 0);
	assert(!running.empty());
	for (unsigned int i = 0; i<running.size(); ++i)
		running[i]->progress(currTime);
}

void AnimatorHolder::pause(void) {
	pauseTime = clock();

	std::vector<Animator *>::iterator it;
	printf("size of running list = %d\n", running.size());

	for (it = running.begin(); it != running.end(); ++it) {
		paused.push_back(*it);
	}
	running.clear();
}

void AnimatorHolder::resume(void) {
	unsigned long pauseOffset = (clock() - pauseTime);

	std::vector<Animator*>::iterator it;
	for (it = paused.begin(); it != paused.end(); ++it) {
		(*it)->timeShift(pauseOffset);
		running.push_back(*it);
	}
	paused.clear();
}

void AnimatorHolder::display(ALLEGRO_BITMAP* at) {

	for (unsigned int i = 0; i<running.size(); ++i)
		running[i]->display(at);
}
