#include "..\..\..\include\Objects\Characters\SideFighter.h"

SideFighter::SideFighter(
		Dim _x, Dim _y, 
		AnimationFilm * film, 
		FrameRangeAnimation * _takeOffAnimation, 
		FrameRangeAnimator * _takeOffAnimator, 
		FrameRangeAnimation * _landAnimation, 
		FrameRangeAnimator * _landAnimator, 
		FrameRangeAnimation * _deathAnimation, 
		FrameRangeAnimator * _deathAnimator,
		FISHES *_fishes) :
	Sprite(_x, _y, film),
	takeOffAnimation(_takeOffAnimation),
	takeOffAnimator(_takeOffAnimator),
	landAnimation(_landAnimation),
	landAnimator(_landAnimator),
	deathAnimation(_deathAnimation),
	deathAnimator(_deathAnimator),
	fishes(_fishes)
{
	AnimatorHolder::animRegister(landAnimator);
	AnimatorHolder::animRegister(deathAnimator);
	AnimatorHolder::animRegister(takeOffAnimator);
	this->lives = 1;
}

void SideFighter::move(int x, int y)
{
	this->x += x;
	this->y += y;
}

void SideFighter::startMoving()
{
}

int SideFighter::getLives()
{
	return this->lives;
}

void SideFighter::incrLives(int n)
{
	this->lives += n;
}

void SideFighter::setLives(int n)
{
	this->lives = n;
}

void SideFighter::shoot(vector<Bird*>* birds)
{
	if (!this->lives) return;
	// Fish (aka. bullets)
	MovingAnimation* bulletAnimation = new MovingAnimation(5, 0, 20, true, 4);
	MovingAnimator* bulletAnimator = new MovingAnimator();

	AnimatorHolder::animRegister(bulletAnimator);
	Fish* fish = new Fish(x + 110, y + 30,
		(AnimationFilm*)
		AnimationFilmHolder::getSingleton()->
		getFilm("doubleFish"),
		bulletAnimation,
		bulletAnimator);
	fishes->push_back(fish);
	fish->startMoving();

	for (unsigned int i = 0; i < birds->size(); i++) {
		if (!birds->at(i)->isDead()) {
			cout << "REGISTER COLLISION! BIRD" << i << " WITH FISH!\n";
			CollisionChecker::getInstance()->
				registerCollisions(birds->at(i), fish);
		}
	}
}

void SideFighter::collisionAction(Sprite * s)
{
	//todo

}
