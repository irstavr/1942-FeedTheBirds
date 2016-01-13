#ifndef _SUPERACE_H
#define _SUPERACE_H

#include "../../Sprites/Sprite.h"
#include "../../Animator/MovingAnimator.h"
#include "../../Animator/TimerTickAnimator.h"
#include "../../Animator/FlashingAnimator.h"

class SuperAce : public Sprite {
public:
	SuperAce::SuperAce(Dim _x, Dim _y, AnimationFilm* film,
		MovingAnimation *_takeOffAnimation, MovingAnimator *_takeOffAnimator,
		MovingAnimation *_landAnimation, MovingAnimator *_landAnimator,
		MovingAnimation *_deathAnimation, MovingAnimator *_deathAnimator);
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
	MovingAnimation *landAnimation, *deathAnimation;
	MovingAnimator *landAnimator, *deathAnimator;
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