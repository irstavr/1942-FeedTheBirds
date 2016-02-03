#include "..\..\include\GameLogic\GameLogic.h"

GameLogic::GameLogic (FrameRangeAnimation *takeOffAnimation,
					  FrameRangeAnimator *takeOffAnimator,
					  MovingPathAnimation *landingAnimation,
					  MovingPathAnimator *landingAnimator,
					  FrameRangeAnimation *deathAnimation,
					  FrameRangeAnimator *deathAnimator,
					  MovingPathAnimation* loopAnimation,
					  MovingPathAnimator* loopAnimator) {
	gameRunning = true;
	superAceKilled = false;
	checkQuadGun = false;
	checkEnemyCrash = false;
	checkSideFighter = false;
	checkExtraLife = false;
	checkNoEnemyBullets = false;
	checkExtraLoop = false;
	check1000Points = false;

	// bonuses
	// used to inform game play to show the POW
	showQuadGun = false;
	showEnemyCrash = false;
	showSideFighter = false;
	showExtraLife = false;
	showNoEnemyBullets = false;
	showExtraLoop = false;
	show1000Points = false;

	profile = new PlayerProfile(std::make_pair(0,0));

	birds = new vector<Bird*>();

	// lists that hold bonus birds 
	// used to check if all are fed in order to
	// show POW on the screen (from gamePlay)
	bonusPow1Birds = new vector<Bird*>;
	bonusPow2Birds = new vector<Bird*>;
	bonusPow3Birds = new vector<Bird*>;
	bonusPow4Birds = new vector<Bird*>;
	bonusPow5Birds = new vector<Bird*>;
	bonusPow6Birds = new vector<Bird*>;
	bonusPow7Birds = new vector<Bird*>;

	superAce = new SuperAce(profile,
							100,
							285,
							(AnimationFilm*)
								AnimationFilmHolder::getSingleton()->
									getFilm("takeOff"),
							takeOffAnimation,
							takeOffAnimator,
							landingAnimation,
							landingAnimator,
							deathAnimation,
							deathAnimator,
							loopAnimation,
							loopAnimator,
		                    this->birds);
}

GameLogic::~GameLogic() {
	gameRunning = false;
	superAceKilled = true;
	checkQuadGun = false;
	checkEnemyCrash = false;
	checkSideFighter = false;
	checkExtraLife = false;
	checkNoEnemyBullets = false;
	checkExtraLoop = false;
	check1000Points = false;
	showQuadGun = false;
	showEnemyCrash = false;
	showSideFighter = false;
	showExtraLife = false;
	showNoEnemyBullets = false;
	showExtraLoop = false;
	show1000Points = false;

	if (birds) birds->clear();
	if (bonusPow1Birds) bonusPow1Birds->clear();
	if (bonusPow2Birds) bonusPow2Birds->clear();
	if (bonusPow3Birds) bonusPow3Birds->clear();
	if (bonusPow4Birds) bonusPow4Birds->clear();
	if (bonusPow5Birds) bonusPow5Birds->clear();
	if (bonusPow6Birds) bonusPow6Birds->clear();
	if (bonusPow7Birds) bonusPow7Birds->clear();
}

Bird* GameLogic::createBird(Dim _x, Dim _y, 
							BirdID birdID,
							BirdLives birdLives,
							BirdSpeed birdSpeed,
							BirdFire birdFire,
							char* filmId,
							FrameRangeAnimation *flyAnimation,
							FrameRangeAnimator *flyAnimator) {
	Bird *bird = new Bird(_x, _y, 
						  birdID,
						  birdLives,
						  birdSpeed,
						  birdFire,
						  (AnimationFilm*)
							AnimationFilmHolder::getSingleton()->
								getFilm(filmId),
								flyAnimation,
								flyAnimator);

	birds->push_back(bird);
	bird->startMoving();

	CollisionChecker::getInstance()->registerCollisions(superAce, bird);

	return bird;
}

bool GameLogic::isRunning() const {
	return gameRunning;
}

bool GameLogic::showBonus(PowerUpType_t powID) {
	
	switch (powID) {
	case quadGun:
		// bonusBirds list is created by AI
		for (unsigned i = 0; i < bonusPow1Birds->size(); i++) {
			// all the birds must be fed
			if (!bonusPow1Birds->at(i)->isFed) {
				return false;
			}
		}
		bonusPow1Birds->clear();
		return true;
		break;
	case enemyCrash:
		// bonusBirds list is created by AI
		for (unsigned i = 0; i < bonusPow2Birds->size(); i++) {
			// all the birds must be fed
			if (!bonusPow2Birds->at(i)->isFed) {
				return false;
			}
		}

		bonusPow2Birds->clear();
		return true;
		break;
	case sideFighters:
		// bonusBirds list is created by AI
		for (unsigned i = 0; i < bonusPow3Birds->size(); i++) {
			// all the birds must be fed
			if (!bonusPow3Birds->at(i)->isFed) {
				return false;
			}
		}

		bonusPow3Birds->clear();
		return true;
		break;
	case extraLife:
		// bonusBirds list is created by AI
		for (unsigned i = 0; i < bonusPow4Birds->size(); i++) {
			// all the birds must be fed
			if (!bonusPow4Birds->at(i)->isFed) {
				return false;
			}
		}

		bonusPow4Birds->clear();
		return true;
		break;
	case noEnemyBullets:
		// bonusBirds list is created by AI
		for (unsigned i = 0; i < bonusPow5Birds->size(); i++) {
			// all the birds must be fed
			if (!bonusPow5Birds->at(i)->isFed) {
				return false;
			}
		}

		bonusPow5Birds->clear();
		return true;
		break;
	case extraLoop:
		// bonusBirds list is created by AI
		for (unsigned i = 0; i < bonusPow6Birds->size(); i++) {
			// all the birds must be fed
			if (!bonusPow6Birds->at(i)->isFed) {
				return false;
			}
		}

		bonusPow6Birds->clear();
		return true;
		break;
	case points1000:
		// bonusBirds list is created by AI
		for (unsigned i = 0; i < bonusPow7Birds->size(); i++) {
			// all the birds must be fed
			if (!bonusPow7Birds->at(i)->isFed) {
				return false;
			}
		}
		bonusPow7Birds->clear();
		return true;
		break;
	}
}

void GameLogic::addBonusBirdToList(PowerUpType_t powID, Bird* bird) {
	switch (powID) {
		case quadGun:
			this->bonusPow1Birds->push_back(bird);
			break;
		case enemyCrash:
			this->bonusPow2Birds->push_back(bird);
			break;
		case sideFighters:
			this->bonusPow3Birds->push_back(bird);
			break;
		case extraLife:
			this->bonusPow4Birds->push_back(bird);
			break;
		case noEnemyBullets:
			this->bonusPow5Birds->push_back(bird);
			break;
		case extraLoop:
			this->bonusPow6Birds->push_back(bird);
			break;
		case points1000:
			this->bonusPow7Birds->push_back(bird);
			break;
	}
}