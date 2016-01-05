#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "allegro5\allegro.h"
#include <cstdio>
#include <functional>

enum animatorstate_t{
	ANIMATOR_FINISHED = 0,
	ANIMATOR_RUNNING = 1,
	ANIMATOR_STOPPED = 2,
};

class Animator
{
public:
	Animator();
	virtual ~Animator();

	typedef void(*ProgressCallback) (Animator*, void*);

	template <typename Tfunc>
	void setOnProgress(const Tfunc& f);
	void stop(void);
	bool hasFinished(void) const;
	virtual void timeShift(unsigned long offset);
	virtual void progress(unsigned long currTime) = 0;

	virtual void display(ALLEGRO_BITMAP* at) = 0;

	//virtual enum animatorType_t getAnimatorType(void);

protected:
	unsigned long lastTime;
	animatorstate_t	state;
	ProgressCallback onProgress;
	void* progressClosure;
	void notifyProgressed(void);

public:



};

#endif