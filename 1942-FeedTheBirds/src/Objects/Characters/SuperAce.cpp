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

}

void SuperAce::collisionAction(Sprite* s) {
	cout << "COLLISION! SUPER ACE!\n";	

	// collision super ace with a bird
	if (Bird* v = dynamic_cast<Bird*>(s)) {
		// kill Bird
		v->removeLife();
		if (v->getLives() == 0) {
			v->setVisibility(false);
		}

		// super ace loses a life
		playerProfile->decrLives();

		// flash super Ace


		//check if game is over
		if (playerProfile->getLives() == 0) {
			// GameOver
			isDead = true;
		}
	}

	// collision super ace with a koutsoulia :P
	if (BirdDropping* v = dynamic_cast<BirdDropping*>(s)) {
		// Super Ace loses a life
		// flashes
		// if 0 lives => gameover
		// kill BirdDropping
		v->setVisibility(false);

		playerProfile->decrLives();

		// flash super Ace


		//check if game is over
		if (playerProfile->isDead()) {
			// GameOver
			isDead = true;
		}
	}
	
	// collision super ace with a POW POW
	/*if (Pow* v = dynamic_cast<Pow*>(s)) {
		// activate LEVELUP on superAce
	}
	*/
}

bool SuperAce::isSuperAceDead(void) {
	if (isDead)
		return true;
	else
		return false;
}