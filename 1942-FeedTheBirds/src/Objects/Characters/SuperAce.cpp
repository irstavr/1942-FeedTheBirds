#include "..\..\..\include\Objects\Characters\SuperAce.h"

SuperAce::SuperAce(PlayerProfile* playerProfile,
	Dim _x, Dim _y, AnimationFilm* film,
	FrameRangeAnimation *_takeOffAnimation,
	FrameRangeAnimator *_takeOffAnimator,
	FrameRangeAnimation *_landAnimation,
	FrameRangeAnimator *_landAnimator,
	FrameRangeAnimation *_deathAnimation,
	FrameRangeAnimator *_deathAnimator,
	MovingPathAnimation* _loopAnimation,
	MovingPathAnimator* _loopAnimator,
	vector<Bird*> *_birds) :
	Sprite(_x, _y, film),
	playerProfile(playerProfile),
	takeOffAnimation(_takeOffAnimation),
	takeOffAnimator(_takeOffAnimator),
	landAnimation(_landAnimation),
	landAnimator(_landAnimator),
	deathAnimation(_deathAnimation),
	deathAnimator(_deathAnimator),
	loopAnimation(_loopAnimation),
	loopAnimator(_loopAnimator),
	birds(_birds)
{
	isDead = false;
	isInvisible = false;
	isShooting = false;
	fishes = new vector<Fish*>();
	hasQuadGun = false;

	this->explosion = new Sprite(this->x-10, this->y,
		(AnimationFilm*)AnimationFilmHolder::getSingleton()->getFilm("bambam"));
	this->explosion->setVisibility(false);

	this->sf1 = new SideFighter(
		this->x, this->y-110, 
		(AnimationFilm*)AnimationFilmHolder::getSingleton()->getFilm("sidefighter"),
		new FrameRangeAnimation(1, 3, 0, 0, 200, false, 21),
		new FrameRangeAnimator(),
		new FrameRangeAnimation(1, 3, 0, 0, 200, false, 22),
		new FrameRangeAnimator(),
		new FrameRangeAnimation(1, 6, 0, 0, 200, false, 23),
		new FrameRangeAnimator(), 
		this->fishes);

	this->sf2 = new SideFighter(
		this->x, this->y+110, 
		(AnimationFilm*)AnimationFilmHolder::getSingleton()->getFilm("sidefighter"), 
		new FrameRangeAnimation(1, 3, 0, 0, 200, false, 24),
		new FrameRangeAnimator(),
		new FrameRangeAnimation(1, 3, 0, 0, 200, false, 25),
		new FrameRangeAnimator(),
		new FrameRangeAnimation(1, 6, 0, 0, 200, false, 26),
		new FrameRangeAnimator(), 
		this->fishes);

	injuredAnimation = new FlashingAnimation(10, 200, 200, 0);
	injuredAnimator = new FlashingAnimator();

}

SuperAce::~SuperAce(void) {
	isInvisible = true;
	isShooting = false;
	isDead = true;
}

void SuperAce::moveUp() {
	if (y>10 && this->canMove) {
		y -= 2;
		this->moveSideFighters(0, -2);
	}
}

void SuperAce::moveDown() {
	if (y < SCREEN_WINDOW_HEIGHT - 120 && this->canMove) {
		y += 2;
		this->moveSideFighters(0, 2);
	}
}

void SuperAce::moveLeft() {
	if (x > 10 && this->canMove) {
		x -= 2;
		this->moveSideFighters(-2, 0);
	}
}

void SuperAce::moveRight() {
	if (x < SCREEN_WINDOW_WIDTH/2 && this->canMove) {
		x += 2;
		this->moveSideFighters(2, 0);
	}
}

void SuperAce::twist(void) {
	// twist only if num of available loops >0
	// and only if super ace is not invisible 
	// (hes not already in a twist)
	if (playerProfile->getLoops() != 0 && !this->isInvisible) {
		this->setInvinsibility(true);
		playerProfile->decrLoops();

		//moving path animation
		loopAnimator->start(this, loopAnimation, getCurrTime());
		AnimatorHolder::markAsRunning(loopAnimator);
		this->setInvinsibility(false);
	}
}

void SuperAce::shoot(vector<Bird*>* birds) {
	// Fish (aka. bullets)
	if (!isInvisible) {
		MovingAnimation* bulletAnimation = new MovingAnimation(5, 0, 20, true, 4);
		MovingAnimator* bulletAnimator = new MovingAnimator();

		AnimatorHolder::animRegister(bulletAnimator);
		Fish* fish = new Fish(x + 50, y-5,
			(AnimationFilm*)
			AnimationFilmHolder::getSingleton()->
			getFilm("doubleFish"),
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
		this->sf1->shoot(birds);
		this->sf2->shoot(birds);

		if (this->hasQuadGun) {
			// Fish (aka. bullets)
			MovingAnimation* bulletAnimation2 = new MovingAnimation(5, 0, 20, true, 4);
			MovingAnimator* bulletAnimator2 = new MovingAnimator();

			AnimatorHolder::animRegister(bulletAnimator2);
			Fish* fish2 = new Fish(x + 110, y + 10,
				(AnimationFilm*)
				AnimationFilmHolder::getSingleton()->
				getFilm("doubleFish"),
				bulletAnimation2,
				bulletAnimator2);
			fishes->push_back(fish2);
			fish2->startMoving();

			for (unsigned int i = 0; i < birds->size(); i++) {
				if (!birds->at(i)->isDead()) {
					cerr << "REGISTER COLLISION! BIRD" << i << " WITH FISH!\n";
					CollisionChecker::getInstance()->
						registerCollisions(birds->at(i), fish2);
				}
			}
		}
	}
}

void SuperAce::displayAll() {
	if (this->isSpriteVisible()) {
		this->display(Rect(0, 0, 0, 0));

		for (unsigned int i = 0; i < fishes->size(); i++) {
			if (fishes->at(i)->isSpriteVisible())
				fishes->at(i)->display(Rect(0, 0, 0, 0));
		}
		this->sf1->displayAll();
		this->sf2->displayAll();
		if (this->explosion->isSpriteVisible()) {
			this->explosion->display(Rect(0, 0, 0, 0));
		}
	}
}

void SuperAce::die() {
	//isDead = true;
	unsigned long time = getCurrTime();
	this->disableMovement();
	this->explosion->setX(this->x+50);
	this->explosion->setY(this->y);
	cerr << "Stuff is happening" << endl;
	this->explosion->setVisibility(true);
	this->deathAnimator->start(explosion, deathAnimation, getCurrTime());
	AnimatorHolder::markAsRunning(this->deathAnimator);
	/*while (time == time + 1000) {
		this->explosion->setVisibility(false);
	}*/
}

void SuperAce::injured(){
	//isInvisible = true;
	startFlashing();
}

void SuperAce::startFlashing(void) {
	fprintf(stdout, "startFlashing -> SuperAce.cpp\n");
	//injuredAnimation->setRepetitions(5);
	injuredAnimator->start(this, injuredAnimation, getCurrTime());
	AnimatorHolder::markAsRunning(injuredAnimator);
}

void SuperAce::stopFlashing(void) {
	fprintf(stdout, "stopFlashing -> SuperAce.cpp\n");
	isInvisible = false;
	AnimatorHolder::markAsSuspended(injuredAnimator);
	AnimatorHolder::cancel(injuredAnimator);
	this->setVisibility(true);
}

void SuperAce::fetchSideFighters()
{
	this->sf1->setLives(1);
	this->sf2->setLives(1);
}

void SuperAce::moveSideFighters(int dx, int dy)
{
	this->sf1->move(dx, dy);
	this->sf2->move(dx, dy);
}

void SuperAce::collisionAction(Sprite* s) {
	if (!isInvisible) {
		cerr << "COLLISION! SUPER ACE!\n";
		/*if (playerProfile->getLives() == 5) {
			// GameOver
			this->die();
		}*/

		// collision super ace with a bird
		if (Bird* v = dynamic_cast<Bird*>(s)) {
			// kill Bird
			v->removeLife();
			if (v->getLives() == 0) {
				v->setVisibility(false);
			}

			// super ace loses a life
			playerProfile->decrLives();
			cerr << "lifes: " << playerProfile->getLives() << "\n";
			
			//check if game is over
			if (playerProfile->getLives() == 0) {
				// GameOver
				this->die();
			}
		}

		// collision super ace with a koutsoulia :P
		if (BirdDropping* v = dynamic_cast<BirdDropping*>(s)) {
			cerr << "COLLISION! SUPER ACE - koutsoulia!\n";
			//remove bird
			v->setVisibility(false);

			//superAce loses life
			playerProfile->decrLives();
			
			// flash super Ace
			injured();

			//check if game is over
			if (playerProfile->isDead()) {
				// GameOver
				this->die();
			}
		}
	}
	
	// collision super ace with a POW POW
	if (PowerUp* v = dynamic_cast<PowerUp*>(s)) {
		if (!v->isExhausted()) {
			switch (v->getType())
			{
			case QuadGun:
				this->hasQuadGun = true;
				break;
			case EnemyCrash:
				for (std::vector<Bird*>::iterator it = this->birds->begin(); it != this->birds->end();it++)
				{
					if (!(*it)->isDead()) (*it)->scare();
				}
				break;
			case SideFighters:
				this->fetchSideFighters();
				break;
			case ExtraLife:
				playerProfile->incrLives();
				break;
			case NoEnemyBullets:
				//todo
				break;
			case ExtraLoop:
				playerProfile->incrLoops();
				break;
			case Points1000:
				playerProfile->incrScore(1000);
				break;
			default:
				break;
			}
		}
	}
}

bool SuperAce::isSuperAceDead(void) {
	return this->isDead;
}