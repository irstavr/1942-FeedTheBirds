#ifndef _POWERUP_H
#define _POWERUP_H
#include "../../Sprites/Sprite.h"
#include "../../Animator/FlashingAnimator.h"
#include "../../Animator/AnimatorHolder.h"

typedef enum PowerUpType {
	quadGun, 
	enemyCrash, 
	sideFighters, 
	extraLife, 
	noEnemyBullets, 
	extraLoop, 
	points1000
} PowerUpType_t;

class PowerUp : public Sprite {

public:
	PowerUpType_t getType();
	void setExhausted();
	bool isExhausted();

	PowerUp(Dim _x, Dim _y, PowerUpType_t type, AnimationFilm* film);
	~PowerUp();

private:
	PowerUpType_t type;
	bool exhasted;

};

#endif