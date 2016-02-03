#include "..\..\..\include\Objects\Characters\SideFighter.h"

SideFighter::SideFighter(
		Dim _x, Dim _y, 
		AnimationFilm * film, 
		MovingAnimation *_appearAnimation,
		MovingAnimator *_appearAnimator,
		MovingAnimation *_disappearAnimation,
		MovingAnimator *_disappearAnimator,
		FISHES *_fishes) :
	Sprite(_x, _y, film),
	appearAnimation(_appearAnimation),
	appearAnimator(_appearAnimator),
	disappearAnimation(_disappearAnimation),
	disappearAnimator(_disappearAnimator),
	fishes(_fishes),
	attached(false)
{
	AnimatorHolder::animRegister(appearAnimator);
	AnimatorHolder::animRegister(disappearAnimator);
	this->lives = 1;
	this->setVisibility(true);
}

void SideFighter::move(int dx, int dy)
{
	this->x += dx;
	this->y += dy;
}

void SideFighter::startMoving()
{
	appearAnimator->start(this, appearAnimation, getCurrTime());
	AnimatorHolder::markAsRunning(appearAnimator);
}

void SideFighter::stopMoving()
{
	if (!attached) {
		attached = true;
		AnimatorHolder::markAsSuspended(appearAnimator);
	}
}

void SideFighter::disappearSideFighter() {
	disappearAnimator->start(this, disappearAnimation, getCurrTime());
	AnimatorHolder::markAsRunning(disappearAnimator);
	attached = false;
}

int SideFighter::getLives()
{
	return this->lives;
}

void SideFighter::setLives(int n)
{
	this->lives = n;
	if(this->lives) this->setVisibility(true);
}

void SideFighter::incrLives()
{
	this->lives++;
	this->setVisibility(true);
}

void SideFighter::decrLives()
{
	//if (!(--this->lives)) this->die();
	--this->lives;
}

void SideFighter::die()
{
	this->setVisibility(false);
	this->lives = 0;
	AnimatorHolder::markAsSuspended(disappearAnimator);
}

void SideFighter::shoot(vector<Bird*>* birds)
{
	if (!(this->lives && this->isSpriteVisible())) return;
	// Fish (aka. bullets)
	MovingAnimation* bulletAnimation = new MovingAnimation(5, 0, 20, true, 4);
	MovingAnimator* bulletAnimator = new MovingAnimator();

	AnimatorHolder::animRegister(bulletAnimator);
	Fish* fish = new Fish(x + 50, y + 10,
		(AnimationFilm*)
		AnimationFilmHolder::getSingleton()->
		getFilm("fish"),
		bulletAnimation,
		bulletAnimator);
	fishes->push_back(fish);
	fish->startMoving();

	for (unsigned int i = 0; i < birds->size(); i++) {
		if (!birds->at(i)->isDead()) {
			cerr << "REGISTER COLLISION! BIRD" << i << " WITH FISH!\n";
			CollisionChecker::getInstance()->
				registerCollisions(birds->at(i), fish);
		}
	}
}

void SideFighter::collisionAction(Sprite * s)
{
	//todo
}

void SideFighter::displayAll() {
	if (this->isSpriteVisible()){
		this->display(Rect(0, 0, 0, 0));
		for (unsigned int i = 0; i < fishes->size(); i++) {
			if (fishes->at(i)->isSpriteVisible())
				fishes->at(i)->display(Rect(0, 0, 0, 0));
		}
	}
}