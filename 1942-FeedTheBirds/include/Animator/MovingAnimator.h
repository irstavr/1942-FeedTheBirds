#ifndef MOVINGANIMATOR_H
#define MOVINGANIMATOR_H

#include "Animator.h"
#include "..\Animation\MovingAnimation.h"
#include "..\Sprites\Sprite.h"


class MovingAnimator : public Animator {
	Sprite*	sprite;
	MovingAnimation* anim;

public:
	MovingAnimator(void);
	~MovingAnimator();

	MovingAnimation* getAnimation(void);
	Sprite* getSprite(void);
	void progress(unsigned long currTime);
	void start(Sprite* s, MovingAnimation* a, unsigned long t);
	void display(Rect at);
};

#endif