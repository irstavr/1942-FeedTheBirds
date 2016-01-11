#ifndef FLASHINGANIMATOR_H
#define FLASHINGANIMATOR_H

#include "Animator.h"
#include "..\Sprites\Sprite.h"
#include "..\Animation\FlashingAnimation.h"

class FlashingAnimator : public Animator {
	Sprite*	sprite;
	FlashingAnimation* anim;
	frame_t repetitions;

public:
	FlashingAnimator(void);
	~FlashingAnimator() {};
	
	void display(ALLEGRO_BITMAP* at) {};

	void progress(unsigned long currTime);
	void start(Sprite* s, FlashingAnimation* a, unsigned long t);
	
};

#endif
