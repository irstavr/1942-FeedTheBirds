#include "..\..\..\include\Objects\Items\PowerUp.h"

PowerUp::PowerUp(Dim _x, 
				Dim _y, 
				PowerUpType_t type,
				AnimationFilm * film) :
	type(type),
	Sprite(_x, _y, film)
{
	this->exhasted = false;
	this->setVisibility(true);
}

PowerUp::~PowerUp() {
	this->exhasted = true;
	this->setVisibility(false);
}

PowerUpType_t PowerUp::getType()
{
	return this->type;
}

void PowerUp::setExhausted()
{
	this->exhasted = true;
}

bool PowerUp::isExhausted()
{
	return this->exhasted;
}
