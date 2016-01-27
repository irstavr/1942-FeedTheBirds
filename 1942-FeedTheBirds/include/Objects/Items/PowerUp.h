#ifndef _POWERUP_H
#define _POWERUP_H
#include "../../Sprites/Sprite.h"
#include "../../Animator/MovingAnimator.h"
#include "../../Animator/AnimatorHolder.h"

typedef enum PowerUpType {QuadGun, EnemyCrash, SideFighters, ExtraLife, NoEnemyBullets, ExtraLoop, Points1000} PowerUpType_t;

class PowerUp:public Sprite {
private:
	int speedx;
	PowerUpType_t type;
	MovingAnimator *flyAnimator;
	MovingAnimation *flyAnimation;
	bool exhasted;
public:
	PowerUpType_t getType();
	void setType(PowerUpType_t _type);
	void exhaust();
	bool isExhausted();
	void move(int x, int y);
	void move();
	void startMoving();
	PowerUp(Dim _x, Dim _y, AnimationFilm* film,
		MovingAnimation *_Animation, MovingAnimator *_Animator);
};


#endif