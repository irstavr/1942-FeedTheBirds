#include "..\..\..\include\Objects\Characters\SuperAce.h"

SuperAce::SuperAce(PlayerProfile* playerProfile,
				Dim _x, Dim _y, AnimationFilm* film,
				FrameRangeAnimation *_takeOffAnimation, 
				FrameRangeAnimator *_takeOffAnimator,
				FrameRangeAnimation *_landAnimation, 
				FrameRangeAnimator *_landAnimator,
				FrameRangeAnimation *_deathAnimation, 
				FrameRangeAnimator *_deathAnimator) :
	Sprite(_x, _y, film),
	playerProfile(playerProfile),
	takeOffAnimation(_takeOffAnimation), 
	takeOffAnimator(_takeOffAnimator),
	landAnimation(_landAnimation), 
	landAnimator(_landAnimator),
	deathAnimation(_deathAnimation), 
	deathAnimator(_deathAnimator) {
	isDead = false;
	isInvisible = false;
	isShooting = false;
	fishes = new vector<Fish*>();
}

SuperAce::~SuperAce(void) {
	isInvisible = true;
	isShooting = false;
	isDead = true;
}

void SuperAce::moveUp() {
	if (y>10) {
		y -= 2;
	}
}

void SuperAce::moveDown() {
	if (y < SCREEN_WINDOW_HEIGHT - 120) {
		y += 2;
	}
}

void SuperAce::moveLeft() {
	if (x > 10) {
		x -= 2;
	}
}

void SuperAce::moveRight() {
	if (x < SCREEN_WINDOW_WIDTH/2) {
		x += 2;
	}
}

void SuperAce::shoot() {
	// Fish (aka. bullets)
	MovingAnimation* bulletAnimation = new MovingAnimation(5, 0, 20, true, 4);
	MovingAnimator* bulletAnimator = new MovingAnimator();

	AnimatorHolder::animRegister(bulletAnimator);
	Fish* fish = new Fish(x+110, y+30,
						(AnimationFilm*)
						AnimationFilmHolder::getSingleton()->
						getFilm("doubleFish"),
						bulletAnimation,
						bulletAnimator);
	fishes->push_back(fish);
	fish->startMoving();
	fish->addToCollisionListWithFishes();
}

void SuperAce::displayAll() {
	if (this->isSpriteVisible()) {
		this->display(Rect(0, 0, 0, 0));
		
		for (unsigned int i = 0; i < fishes->size(); i++) {
			if (fishes->at(i)->isSpriteVisible())
				fishes->at(i)->display(Rect(0, 0, 0, 0));
		}
	}
}

void SuperAce::die() {
	isDead = true;
}

void SuperAce::collisionAction() {
	cout << "COLLISION! SUPER ACE!\n";
	//super ace loses a life
	playerProfile->decrLives();

	// flash super Ace
	//this->flash();?

	//check if game is over
	if (playerProfile->getLives() == 0) {
		// GameOver
		this->die();
	}
}

bool SuperAce::isSuperAceDead(void) {
	if (isDead)
		return true;
	else
		return false;
}