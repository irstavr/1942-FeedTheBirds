#ifndef _FISH_H
#define _FISH_H

#include "../../Sprites/Sprite.h"
#include "../../Animator/MovingAnimator.h"
#include "../../Animator/TimerTickAnimator.h"
#include "../../Animator/FlashingAnimator.h"
#include "../../Animator/FrameRangeAnimator.h"
#include <utility>
#include <vector>

using namespace std;

typedef vector<COORDS> DOTS;

class Fish :public Sprite {

private:
	int speedY, direction, speedX;

	MovingAnimation *flyAnimation;
	MovingAnimator *flyAnimator;
	FlashingAnimation *flashAnimation;
	FlashingAnimator *flashAnimator;
	TickAnimation *tickAnimation;
	TimerTickAnimator *timerTick;

	bool isInvisible;
	bool isMetWithBird;

public:
	Fish(int d, int t);

	Fish::Fish(Dim _x, Dim _y, AnimationFilm* film,
		MovingAnimation *_flyAnimation, MovingAnimator *_flyAnimator,
		FlashingAnimation *_flashAnimation, FlashingAnimator *_flashingAnimator);
	~Fish(void);

	/*Calculate the (x,y) of every bullet*/
	void move(float dt, float &x, float&y);
	/*check if num is in [x, y]*/
	bool inRange(float x, float y, float num);
};

#endif