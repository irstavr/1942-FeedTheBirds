#ifndef ANIMATORHOLDER_H
#define ANIMATORHOLDER_H

#include "allegro5\allegro.h"
#include <list>
#include <vector>

#include "Animator.h"

class AnimatorHolder {
	static std::list<Animator*> running, suspended;

public:
	static void animRegister(Animator* a);
	static void cancel(Animator* a);
	static void markAsRunning(Animator* a);
	static void markAsSuspended(Animator* a);
	static void progress(unsigned long currTime);
	static void pause(void);
	static void resume(void);
	static void display(ALLEGRO_BITMAP* at);

	static void timeShiftAnimators(unsigned long addTime);
	static std::vector<Animator*> getAnimators(enum animatorType_t);
	static std::vector<Animator*> getAnimators(animatorType_t start, animatorType_t end);


};

#endif