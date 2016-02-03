#include "..\..\..\include\Objects\Characters\SuperAce.h"

SuperAce::SuperAce(PlayerProfile* playerProfile,
					Dim _x, Dim _y, AnimationFilm* film,
					FrameRangeAnimation *_takeOffAnimation,
					FrameRangeAnimator *_takeOffAnimator,
					MovingPathAnimation *_landAnimation,
					MovingPathAnimator *_landAnimator,
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
		birds(_birds),
		film(film),
		injuredTime(-1),
		loopTime(-1),
		landingTime(-1),
		takeOffTime(-1),
		explosionTime(-1),
		isInjured(false),
		isLooping(false),
		isExploding(false),
		isLanding(false),
		isTakingOff(false),
		isDead(false),
		isInvincible(false),
		isShooting(false),
		hasQuadGun(false),
		hasSideFighter(false),
		noEnemiesBullets(false),
		noEnemyBulletsTime(-1)
{
	fishes = new vector<Fish*>();

	this->explosion = new Sprite(this->x-10, this->y,
		(AnimationFilm*)AnimationFilmHolder::getSingleton()->getFilm("bambam"));
	this->explosion->setVisibility(false);

	injuredAnimation = new FlashingAnimation(10, 200, 200, 0);
	injuredAnimator = new FlashingAnimator();
}

SuperAce::~SuperAce(void) {
	injuredTime = -1;
	loopTime = -1;
	explosionTime = -1;

	isInjured = false;
	isLooping = false;
	isExploding = false;
	isLanding = false;
	isTakingOff = false;
	isInvincible = false;
	isShooting = false;
	hasQuadGun = false;
	isDead = false;
}

void SuperAce::fetchSideFighters() {
	this->disableMovement();
	MovingAnimation* appear_sf1Animation = new MovingAnimation(0, 2, 5, true, 500);
	MovingAnimator* appear_sf1Animator = new MovingAnimator();
	MovingAnimation* appear_sf2Animation = new MovingAnimation(0, -2, 5, true, 501);
	MovingAnimator* appear_sf2Animator = new MovingAnimator();
	MovingAnimation* disappear_sf1Animation = new MovingAnimation(0, -2, 5, true, 502);
	MovingAnimator* disappear_sf1Animator = new MovingAnimator();
	MovingAnimation* disappear_sf2Animation = new MovingAnimation(0, 2, 5, true, 503);
	MovingAnimator* disappear_sf2Animator = new MovingAnimator();

	this->sf1 = new SideFighter(this->x-50, -50,
		(AnimationFilm*)
		AnimationFilmHolder::getSingleton()
			->getFilm("sidefighter"),
		appear_sf1Animation,
		appear_sf1Animator,
		disappear_sf1Animation,
		disappear_sf1Animator,
		this->fishes);

	this->sf2 = new SideFighter(this->x-50, SCREEN_WINDOW_HEIGHT+40,
		(AnimationFilm*)AnimationFilmHolder::getSingleton()
			->getFilm("sidefighter"),
		appear_sf2Animation,
		appear_sf2Animator,
		disappear_sf2Animation,
		disappear_sf2Animator,
		this->fishes);

	AnimatorHolder::animRegister(appear_sf1Animator);
	AnimatorHolder::animRegister(appear_sf2Animator);
	AnimatorHolder::animRegister(disappear_sf1Animator);
	AnimatorHolder::animRegister(disappear_sf2Animator);
	sf1->startMoving();
	sf2->startMoving();

	hasSideFighter = true;
	this->sf1->setLives(1);
	this->sf2->setLives(1);
}

void SuperAce::removeSideFighters() {
	sf1->disappearSideFighter();
	sf2->disappearSideFighter();
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
	if (playerProfile->getLoops() != 0 && !this->isInvincible) {
		this->isLooping = true;
		this->setInvincibility(true);
		// our trick ! oho ho ho
		loopTime = getCurrTime();

		playerProfile->decrLoops();

		// moving path animation
		loopAnimator->start(this, loopAnimation, getCurrTime());
		AnimatorHolder::markAsRunning(loopAnimator);
	}
}

void SuperAce::startTakeOff(void) {
	this->isTakingOff = true;
	this->takeOffTime = getCurrTime();
	this->setX(10);
	this->setY(300);
	this->disableMovement();
	takeOffAnimator->start(this, takeOffAnimation, getCurrTime());
	AnimatorHolder::markAsRunning(takeOffAnimator);
}

void SuperAce::startLanding(void) {
	this->isLanding = true;
	this->landingTime = getCurrTime();
	this->disableMovement();
	this->setX(x);
	this->setY(285);
	landAnimator->start(this, landAnimation, getCurrTime());
	AnimatorHolder::markAsRunning(landAnimator);
}

void SuperAce::shoot(vector<Bird*>* birds) {
	// Fish (aka. bullets)
	if (!isInvincible) {
		MovingAnimation* bulletAnimation = new MovingAnimation(2, 0, 5, true, 4);
		MovingAnimator* bulletAnimator = new MovingAnimator();

		AnimatorHolder::animRegister(bulletAnimator);
		Fish* fish = new Fish(x + 20, y-40,
								(AnimationFilm*)
									AnimationFilmHolder::getSingleton()->
									getFilm("doubleFish"),
								bulletAnimation,
								bulletAnimator);
		fishes->push_back(fish);
		fish->startMoving();

		for (unsigned int i = 0; i < birds->size(); i++) {
			if (!birds->at(i)->isDead()) {
				CollisionChecker::getInstance()->
					registerCollisions(birds->at(i), fish);
			}
		}

		if (hasSideFighter) {
			this->sf1->shoot(birds);
			this->sf2->shoot(birds);
		}

		if (this->hasQuadGun) {
			// Fish (aka. bullets)
			MovingAnimation* bulletAnimation2 = new MovingAnimation(2, 0, 5, true, 4);
			MovingAnimator* bulletAnimator2 = new MovingAnimator();

			AnimatorHolder::animRegister(bulletAnimator2);
			Fish* fish2 = new Fish(x+20 , y +10,
				(AnimationFilm*)
				AnimationFilmHolder::getSingleton()->
				getFilm("doubleFish"),
				bulletAnimation2,
				bulletAnimator2);
			fishes->push_back(fish2);
			fish2->startMoving();

			for (unsigned int i = 0; i < birds->size(); i++) {
				if (!birds->at(i)->isDead()) {
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

		displayFishes();

		if (hasSideFighter) {
			this->sf1->displayAll();
			this->sf2->displayAll();
			if (!sf1->attached||!sf2->attached) {
				if (sf1->y > this->y - 80) {
					sf1->stopMoving();
				}
				if (sf2->y < this->y + 30) {
					sf2->stopMoving();
				}

				//when out of screen
				if (sf1->y < -80) {
					hasSideFighter = false;
					sf1->die();
				}

				if (sf2->y > SCREEN_WINDOW_HEIGHT + 80) {
					hasSideFighter = false;
					sf2->die();
				}
				this->enableMovement();
			}
		}
	}
	if (this->explosion->isSpriteVisible()) {
		this->explosion->display(Rect(0, 0, 0, 0));
	}
}

void SuperAce::displayFishes()
{
	for (unsigned int i = 0; i < fishes->size(); i++) {
		// show fish if visible and alive
		if (fishes->at(i)->isSpriteVisible()) {
			fishes->at(i)->display(Rect(0, 0, 0, 0));
		}
	}
}

void SuperAce::explode() {
	isExploding = true;

	this->setInvincibility(true);
	explosionTime = getCurrTime();

	this->disableMovement();
	this->explosion->setX(this->x);
	this->explosion->setY(this->y);
	this->explosion->setVisibility(true);
	this->deathAnimator->start(explosion, deathAnimation, getCurrTime());
	AnimatorHolder::markAsRunning(this->deathAnimator);
	die();
}

void SuperAce::die() {
	isDead = true;
}

void SuperAce::injured(){
	this->isInjured = true;
	this->isInvincible = true;

	this->injuredTime = getCurrTime();
	startFlashing();
}

void SuperAce::startFlashing(void) {
	injuredAnimator->start(this, injuredAnimation, getCurrTime());
	AnimatorHolder::markAsRunning(injuredAnimator);
}

void SuperAce::stopFlashing(void) {
	isInvincible = false;
	AnimatorHolder::markAsSuspended(injuredAnimator);
	AnimatorHolder::cancel(injuredAnimator);
	this->setVisibility(true);
}

void SuperAce::moveSideFighters(int dx, int dy)
{
	if (hasSideFighter) {
		this->sf1->move(dx, dy);
		this->sf2->move(dx, dy);
	}
}

void SuperAce::collisionAction(Sprite* s) {
	if (!isInvincible) {

		// collision super ace with a bird
		if (Bird* v = dynamic_cast<Bird*>(s)) {
			// kill Bird
			if (!hasSideFighter) {
				v->removeLife();
				if (v->getLives() == 0) {
					v->setVisibility(false);
				}
				// super ace loses a life
				playerProfile->decrLives();
				// flash super Ace
				injured();
				//check if game is over
				if (playerProfile->getLives() == 0) {
					// GameOver
					this->explode();
				}
			}
			else {
				removeSideFighters();
			}
		}

		// collision super ace with a koutsoulia :P
		if (BirdDropping* v = dynamic_cast<BirdDropping*>(s)) {
			//remove bird
			v->setVisibility(false);

			if (!hasSideFighter) {
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
			else {
				removeSideFighters();
			}
		}
	}
	
	// collision super ace with a POW POW
	if (PowerUp* v = dynamic_cast<PowerUp*>(s)) {

		if (!v->isExhausted()) {
			v->setExhausted();
			v->setVisibility(false);

			switch (v->getType())
			{
			case quadGun:
				this->hasQuadGun = true;
				break;
			case enemyCrash:
				for (std::vector<Bird*>::iterator it = this->birds->begin(); it != this->birds->end();it++)
				{
					if (!(*it)->isDead()) 
						(*it)->scare();
				}
				break;
			case sideFighters:
				this->fetchSideFighters();
				break;
			case extraLife:
				playerProfile->incrLives();
				break;
			case noEnemyBullets:
				this->noEnemiesBullets = true;
				noEnemyBulletsTime = getCurrTime();

				for (std::vector<Bird*>::iterator it = this->birds->begin(); it != this->birds->end(); it++)
				{
					if (!(*it)->isDead())
						(*it)->canShoot = false;
				}
				break;
			case extraLoop:
				playerProfile->incrLoops();
				break;
			case points1000:
				ScoreBoard::getInstance().incrScore(1000);
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