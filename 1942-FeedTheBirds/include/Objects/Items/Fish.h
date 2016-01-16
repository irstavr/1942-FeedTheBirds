#ifndef _FISH_H
#define _FISH_H

#include "../../Sprites/Sprite.h"
#include "../../Animator/MovingAnimator.h"
#include "../../Animator/TimerTickAnimator.h"
#include "../../Animator/FlashingAnimator.h"
#include "../../Animator/AnimatorHolder.h"
#include <utility>
#include <vector>

using namespace std;

typedef pair<float, float> COORDS;
typedef vector<COORDS> DOTS;

class Fish :public Sprite {

private:
	int speedX = 10;

	MovingAnimation *flyAnimation;
	MovingAnimator *flyAnimator;
	TickAnimation *tickAnimation;
	TimerTickAnimator *timerTick;

	bool isInvisible;
	bool isMetWithBird;

public:

	Fish::Fish(Dim _x, Dim _y, AnimationFilm* film,
		MovingAnimation *_flyAnimation, MovingAnimator *_flyAnimator);
	~Fish(void);

	/*Calculate the (x,y) of every bullet*/
	void move(float dt, float &x, float&y);
	/*check if num is in [x, y]*/
	bool inRange(float x, float y, float num);

	void Fish::startMoving(void);
};

#endif