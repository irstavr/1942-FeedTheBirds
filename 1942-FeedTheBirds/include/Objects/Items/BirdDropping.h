#ifndef _BIRDDROPPING_H
#define _BIRDDROPPING_H

#include "../../Sprites/Sprite.h"
#include "../../Animator/MovingAnimator.h"
#include "../../Animator/TimerTickAnimator.h"
#include "../../Animator/FlashingAnimator.h"
#include "../../Animator/AnimatorHolder.h"
#include <utility>
#include <vector>

	using namespace std;

	typedef vector<COORDS> DOTS;


	class BirdDropping : public Sprite {

	private:
		int speedX = 10;

		MovingAnimation *flyAnimation;
		MovingAnimator *flyAnimator;
		TickAnimation *tickAnimation;
		TimerTickAnimator *timerTick;

		bool isInvisible;
		bool isMetWithBird;

	public:

		BirdDropping::BirdDropping(Dim _x, Dim _y, AnimationFilm* film,
			MovingAnimation *_flyAnimation, MovingAnimator *_flyAnimator);
		~BirdDropping(void);

		/*Calculate the (x,y) of every bullet*/
		void move(float dt, float &x, float&y);
		/*check if num is in [x, y]*/
		bool inRange(float x, float y, float num);

		void BirdDropping::startMoving(void);
	};

#endif