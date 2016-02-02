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
	SuperAce(PlayerProfile * playerProfile, Dim _x, Dim _y, AnimationFilm * film, FrameRangeAnimation * _takeOffAnimation, FrameRangeAnimator * _takeOffAnimator, MovingPathAnimation * _landAnimation, MovingPathAnimator * _landAnimator, FrameRangeAnimation * _deathAnimation, FrameRangeAnimator * _deathAnimator, MovingPathAnimation * _loopAnimation, MovingPathAnimator * _loopAnimator, vector<Bird*>* _birds);
	~SuperAce(void);

	vector<Bird*> *birds;

	FrameRangeAnimation *takeOffAnimation;
	FrameRangeAnimator *takeOffAnimator;
	AnimationFilm* film;

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
	bool isSuperAceDead();
	void displayAll();
	virtual void collisionAction(Sprite* s);
	void injured();
	void startFlashing(void);
	void stopFlashing(void);
	void fetchSideFighters();
	void removeSideFighters();
	void displayFishes();

	// flags
	bool isInvincible;
	bool isLanding;
	bool isInjured;
	bool isLooping;
	bool isExploding;
	
	// hacking use
	unsigned long injuredTime;
	unsigned long explosionTime;
	unsigned long loopTime;
	unsigned long landingTime;

	void setInvincibility(bool _inv) { isInvincible = _inv; };

	// bonuses
	bool hasQuadGun;
	bool hasEnemyCrash;
	bool hasSideFighter;
	bool hasExtraLife;
	bool hasNoEnemyBullets;
	bool hasExtraLoop;
	bool has1000Points;
	
	bool noEnemiesBullets;
	unsigned long noEnemyBulletsTime;

private:
	float dx, dy;
	float speedx, speedy;
	FISHES *fishes;

	SideFighter *sf1;
	SideFighter *sf2;

	bool isDead;
	bool isShooting;
	void moveSideFighters(int dx, int dy);

	PlayerProfile* playerProfile;
	Sprite* explosion;
	FrameRangeAnimation *deathAnimation;
	FrameRangeAnimator *deathAnimator;
	FlashingAnimation *flashAnimation;
	FlashingAnimator *flashAnimator;
	TickAnimation *tickAnimation;
	TimerTickAnimator *timerTick;
	MovingPathAnimation * loopAnimation;
	MovingPathAnimator* loopAnimator;
	FlashingAnimation* injuredAnimation;
	FlashingAnimator* injuredAnimator;
	MovingPathAnimation* landAnimation;
	MovingPathAnimator* landAnimator;
	
};
#endif