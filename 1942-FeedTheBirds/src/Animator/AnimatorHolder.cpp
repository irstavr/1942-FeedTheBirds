#include "../../include/Animator/AnimatorHolder.h"

std::list<Animator*> AnimatorHolder::running;
std::list<Animator*> AnimatorHolder::suspended;
std::list<Animator*> AnimatorHolder::paused;

unsigned long AnimatorHolder::pauseTime;

void AnimatorHolder::animRegister(Animator* a) {
	//assert(a);
	suspended.push_back(a);
}

void AnimatorHolder::cancel(Animator* a) {
	//assert(!suspended.empty());
	//assert(a);

	//std::vector<Animator*>::iterator it = std::find(suspended.begin(), suspended.end(), a);
	//assert(it != suspended.end());
	suspended.remove(a);
}

void AnimatorHolder::markAsRunning(Animator* a) {
	//assert(!suspended.empty());
	//assert(a);
	//std::vector<Animator*>::iterator it = std::find(suspended.begin(), suspended.end(), a);
	//assert(it != suspended.end());
	suspended.remove(a);
	running.push_back(a);
}

void AnimatorHolder::markAsSuspended(Animator* a) {
	//assert(!running.empty());
	//assert(a);

	//std::vector<Animator*>::iterator it = std::find(running.begin(), running.end(), a);
	//assert(it != running.end());
	running.remove(a);
	suspended.push_back(a);
}


void AnimatorHolder::progress(unsigned long currTime) {
	//assert(currTime >= 0);
	assert(!running.empty());

	//fprintf(stdout, "progress \n");
	std::for_each(running.begin(), running.end(), ProgressFunctor(currTime));
	//std::list<Animator *>::iterator i;
	//for (i = pending_suspention.begin(); i != pending_suspention.end(); i++)
	//	MarkAsSuspended(*i);

	//pending_suspention.clear();
}

void AnimatorHolder::pause(void) {
	pauseTime = clock();

	std::list<Animator *>::iterator it;
	printf("size of running list = %d\n", running.size());

	for (it = running.begin(); it != running.end(); ++it) {
		paused.push_back(*it);
	}
	running.clear();
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
/*
void AnimatorHolder::display(ALLEGRO_BITMAP* at) {

	for (unsigned int i = 0; i<running.size(); ++i)
		running[i]->display(at);
}
*/