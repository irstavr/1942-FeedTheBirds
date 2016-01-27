#include "..\..\..\include\Objects\Items\PowerUp.h"

PowerUpType_t PowerUp::getType()
{
	return this->type;
}

void PowerUp::setType(PowerUpType_t _type)
{
	this->type = _type;
}

void PowerUp::exhaust()
{
	this->exhasted = true;
}

bool PowerUp::isExhausted()
{
	return this->exhasted;
}

void PowerUp::move(int dx, int dy)
{
	x += dx;
	x += dy;
}

void PowerUp::move()
{
	x += speedx;
}

void PowerUp::startMoving()
{
	fprintf(stdout, "startMoving -> PowerUp.cpp\n");
	flyAnimator->start(this, flyAnimation, getCurrTime());
	AnimatorHolder::markAsRunning(flyAnimator);
}

PowerUp::PowerUp(
	Dim _x, 
	Dim _y, 
	AnimationFilm * film, 
	MovingAnimation * _flyAnimation,
	MovingAnimator * _flyAnimator) :
	Sprite(_x, _y, film),
	flyAnimation(_flyAnimation),
	flyAnimator(_flyAnimator)
{
	this->exhasted = false;
	this->setVisibility(true);
	this->speedx = 10;
}
