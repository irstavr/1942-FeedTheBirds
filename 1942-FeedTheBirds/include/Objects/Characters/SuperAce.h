#ifndef _SUPERACE_H
#define _SUPERACE_H

#include "..\..\Sprites\Sprite.h"
#include "..\Items\Fish.h"
#include "..\..\Animator\FrameRangeAnimator.h"
#include "..\..\GameLogic\PlayerProfile.h"
#include "..\..\Animator\FlashingAnimator.h"
#include "..\..\Animation\AnimationFilmHolder.h"


typedef vector<Fish*> FISHES;

class SuperAce : public Sprite {
public:
	SuperAce::SuperAce(PlayerProfile* playerProfile, Dim _x, Dim _y, AnimationFilm* film,
						FrameRangeAnimation *_takeOffAnimation, FrameRangeAnimator *_takeOffAnimator,
						FrameRangeAnimation *_landAnimation, FrameRangeAnimator *_landAnimator,
						FrameRangeAnimation *_deathAnimation, FrameRangeAnimator *_deathAnimator);
	~SuperAce(void);

	void shoot();
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
	void die(void);
	static bool deathCompleted(void);
	bool isSuperAceDead();
	void playDeathAnimation();
	void gotHit();
	void setInvinsibility(bool _inv) { isInvisible = _inv; };
	void displayAll();
	virtual void collisionAction();
	//virtual void collisionAction(Sprite* s);

private:
	float dx, dy;
	float speedx, speedy;
	FISHES *fishes;

	bool isDead;
	bool isInvisible;
	bool isShooting;
	bool hasSideFighter;
	//bool hasQuadGun;

	PlayerProfile* playerProfile;
	FrameRangeAnimation *takeOffAnimation, *landAnimation, *deathAnimation;
	FrameRangeAnimator *takeOffAnimator, *landAnimator, *deathAnimator;
	FlashingAnimation *flashAnimation;
	FlashingAnimator *flashAnimator;
	TickAnimation *tickAnimation;
	TimerTickAnimator *timerTick;

	static void shootingCompleted(Animator*, void *closure);
	static void invinsibilityEnded(Animator *, void *closure);

};
#endif