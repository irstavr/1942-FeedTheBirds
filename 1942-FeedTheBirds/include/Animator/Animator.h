#ifndef AN_H
#define AN_H

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

	typedef void(*ProgressCallback) (Animator*, void*);

	template <typename Tfunc>
	void setOnProgress(const Tfunc& f);
	void stop(void);
	bool hasFinished(void) const;
	virtual void timeShift(unsigned long offset);
	virtual void progress(unsigned long currTime) = 0;

protected:
	unsigned long lastTime;
	animatorstate_t	state;
	ProgressCallback onProgress;
	void* progressClosure;

	void notifyProgressed(void);

public:



};

#endif