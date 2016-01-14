#ifndef FRAMERANGEANIMATOR_H
#define FRAMERANGEANIMATOR_H

#include "Animator.h"
#include "../Sprites/Sprite.h"
#include "../Animation/FrameRangeAnimation.h"

class FrameRangeAnimator : public Animator {
	Sprite*			sprite;
	FrameRangeAnimation*	anim;
	frame_t			currFrame;

	public:
	void progress(unsigned long currTime);
	void start(Sprite* s, FrameRangeAnimation* a, unsigned long t);
	FrameRangeAnimator(void);
	~FrameRangeAnimator(){}

	void display(ALLEGRO_BITMAP* at) {};
};

#endif