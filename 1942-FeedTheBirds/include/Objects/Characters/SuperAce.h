#ifndef _SUPERACE_H
#define _SUPERACE_H

#include "..\..\Sprites\Sprite.h"
#include "..\..\Animator\MovingAnimator.h"
#include "..\..\Animator\TimerTickAnimator.h"
#include "..\..\Animator\FlashingAnimator.h"
#include "..\..\Animator\FrameRangeAnimator.h"
#include "..\..\Animator\MovingPathAnimator.h"
#include "..\..\Animation\AnimationFilmHolder.h"
#include "..\..\GameAction\CollisionChecker.h"
#include "..\Items\Fish.h"
#include "..\Items\BirdDropping.h"
#include "..\Items\PowerUp.h"
#include "./Bird.h"
#include "./SideFighter.h"
#include "..\..\GameLogic\PlayerProfile.h"
#include "..\..\GameLogic\ScoreBoard.h"

typedef vector<Fish*> FISHES;

class SuperAce : public Sprite {
public:
	SuperAce::SuperAce(PlayerProfile* playerProfile, Dim _x, Dim _y, AnimationFilm* film,
						FrameRangeAnimation *_takeOffAnimation, FrameRangeAnimator *_takeOffAnimator,
						FrameRangeAnimation *_landAnimation, FrameRangeAnimator *_landAnimator,
						FrameRangeAnimation *_deathAnimation, FrameRangeAnimator *_deathAnimator,
						MovingPathAnimation* _loopAnimation, MovingPathAnimator* _loopAnimator, vector<Bird*> *_birds);
	~SuperAce(void);

	void shoot(vector<Bird*>* birds);
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void twist(void);
	void startLanding(void);
	void startTakeOff(void);
	void die(void);
	void explode(void);
	static bool deathCompleted(void);
	bool isSuperAceDead();

	void setInvincibility(bool _inv) { isInvincible = _inv; };

	void displayAll();
	virtual void collisionAction(Sprite* s);
	void injured();
	void startFlashing(void);
	void stopFlashing(void);
	void fetchSideFighters();
	FrameRangeAnimation *takeOffAnimation;
	FrameRangeAnimator *takeOffAnimator;
	AnimationFilm* film;

private:
	vector<Bird*> *birds;
	float dx, dy;
	float speedx, speedy;
	FISHES *fishes;

	SideFighter *sf1;
	SideFighter *sf2;

	bool isDead;
	bool isInvincible;
	bool isShooting;
	bool hasSideFighter;
	bool hasQuadGun;
	void moveSideFighters(int dx, int dy);

	PlayerProfile* playerProfile;
	Sprite* explosion;
	FrameRangeAnimation *landAnimation, *deathAnimation;
	FrameRangeAnimator *landAnimator, *deathAnimator;
	FlashingAnimation *flashAnimation;
	FlashingAnimator *flashAnimator;
	TickAnimation *tickAnimation;
	TimerTickAnimator *timerTick;
	MovingPathAnimation * loopAnimation;
	MovingPathAnimator* loopAnimator;
	FlashingAnimation* injuredAnimation;
	FlashingAnimator* injuredAnimator;

	static void shootingCompleted(Animator*, void *closure);
	static void invinsibilityEnded(Animator *, void *closure); 
	
};
#endif