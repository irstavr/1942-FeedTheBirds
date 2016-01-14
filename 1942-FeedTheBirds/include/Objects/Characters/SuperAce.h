#ifndef _SUPERACE_H
#define _SUPERACE_H

#include "../../Sprites/Sprite.h"
#include "../../Animator/MovingAnimator.h"
#include "../../Animator/TimerTickAnimator.h"
#include "../../Animator/FlashingAnimator.h"
#include "../../Animator/FrameRangeAnimator.h"

class SuperAce : public Sprite {
public:
	SuperAce::SuperAce(Dim _x, Dim _y, AnimationFilm* film,
		FrameRangeAnimation *_takeOffAnimation, FrameRangeAnimator *_takeOffAnimator,
		FrameRangeAnimation *_landAnimation, FrameRangeAnimator *_landAnimator,
		FrameRangeAnimation *_deathAnimation, FrameRangeAnimator *_deathAnimator);
	~SuperAce(void);

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	//virtual void move(int dx, int dy);
	void startLanding(void);
	void startTakeOff(void);
	//void removeLife(void);
	//void addLife(void);
	unsigned int getLives(void);
	//virtual void collisionAction(Sprite *s);
	void die(void);
	static bool deathCompleted(void);
	bool isDead();
	void playDeathAnimation();
	void gotHit();
	void setInvinsibility(bool _inv) { isInvisible = _inv; };

private:
	FrameRangeAnimation *takeOffAnimation, *landAnimation, *deathAnimation;
	FrameRangeAnimator *takeOffAnimator, *landAnimator, *deathAnimator;
	FlashingAnimation *flashAnimation;
	FlashingAnimator *flashAnimator;
	TickAnimation *tickAnimation;
	TimerTickAnimator *timerTick;

	bool isInvisible;
	bool isShooting;
	bool hasSideFighter;
	//bool hasQuadGun;

	static void shootingCompleted(Animator*, void *closure);
	static void invinsibilityEnded(Animator *, void *closure);

};

#endif