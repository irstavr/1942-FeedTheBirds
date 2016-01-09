#ifndef ANIMATORHOLDER_H
#define ANIMATORHOLDER_H

#include "Animator.h"

#include "allegro5\allegro.h"

#include <list>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <iostream>

using namespace std;

class AnimatorHolder {
	static std::vector<Animator*> running, suspended, paused;
	static unsigned long pauseTime;

public:
	static void animRegister(Animator* a);
	static void cancel(Animator* a);
	static void markAsRunning(Animator* a);
	static void markAsSuspended(Animator* a);

	static void progress(unsigned long currTime);
	static void pause(void);
	static void resume(void);
	static void display(ALLEGRO_BITMAP* at);


};

#endif