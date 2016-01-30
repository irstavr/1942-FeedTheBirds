#ifndef MOVINGPATHANIMATOR_H
#define MOVINGPATHANIMATOR_H

#include "Animator.h"
#include "..\Sprites\Sprite.h"
#include "..\Animation\MovingPathAnimation.h"

class MovingPathAnimator : public Animator {
	Sprite* sprite;
	MovingPathAnimation* anim;
	frame_t currFrame;
	std::list<PathEntry>::iterator currEntry;
	int currIndex;
	bool handleFrames;

public:
	MovingPathAnimator(void);
	~MovingPathAnimator() {}

	void setHandleFrames(bool b);
	void progress(unsigned long currTime);
	void start(Sprite* s, MovingPathAnimation* a, unsigned long t);

	void display(ALLEGRO_BITMAP* at) {};


	MovingPathAnimation* getAnimation(void)
	{
		return anim;
	}

	Sprite* getSprite(void)
	{
		return sprite;
	}

	int getCurrIndex() { return currIndex; }
	void setCurrIndex(int index) { currIndex = index; }
	MovingPathAnimator* clone() const;
};

#endif