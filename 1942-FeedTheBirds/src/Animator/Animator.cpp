#include "../../include/Animator/Animator.h"

Animator::Animator(void) :
	lastTime(0), state(ANIMATOR_FINISHED),
	onProgress((ProgressCallback)0), 
	progressClosure((void*)0) {
}

Animator::~Animator() {

}

bool Animator::hasFinished(void) const {
	return state != ANIMATOR_RUNNING;
}

template <typename Tfunc>
void setOnProgress(const Tfunc& f) {
	onProgress = f;
}

void Animator::stop(void) {
	if (!hasFinished()) {
		state = ANIMATOR_STOPPED;
		notifyProgressed();
	}
}

void Animator::notifyProgressed(void) {
	if (onProgress)
		(*onProgress)(this, progressClosure);
}

void Animator::timeShift(unsigned long offset) { lastTime += offset; }