#ifndef ANIMATORHOLDER_H
#define ANIMATORHOLDER_H

#include "Animator.h"
#include "allegro5\allegro.h"
#include <list>
#include <vector>
#include <algorithm>
#include <assert.h>

class AnimatorHolder {
private:
	static std::list<Animator*> running;
	static std::list<Animator*> suspended;
	static std::list<Animator*> paused;
	static unsigned long pauseTime;

	class ProgressFunctor : public std::unary_function<Animator*, void> {
		unsigned long t;
	public:
		explicit ProgressFunctor(unsigned long _t) : 
				t(_t) {
		}
		
		void operator()(Animator* a) const { 
			if (!(a->hasFinished())) {
				a->progress(t);
			}
		}
	};
public:
	static void animRegister(Animator* a);
	static void cancel(Animator* a);
	static void markAsRunning(Animator* a);
	static void markAsSuspended(Animator* a);

	static void progress(unsigned long currTime);
	static void pause();
	static void pauseAllExcept(Animator* anim);
	static void resume(void);
};
#endif