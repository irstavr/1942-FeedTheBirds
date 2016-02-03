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

	birds->clear();
	bonusPow1Birds->clear();
	bonusPow2Birds->clear();
	bonusPow3Birds->clear();
	bonusPow4Birds->clear();
	bonusPow5Birds->clear();
	bonusPow6Birds->clear();
	bonusPow7Birds->clear();
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

bool GameLogic::showBonus(PowerUpType_t bonus, BIRDS* &bonusBirds) {
	// bonusBirds list is created by AI
	for (unsigned i = 0; i < bonusBirds->size(); i++) {
		// all the birds must be fed
		if (!bonusBirds->at(i)->isFed) {
			return false;
		}
	}
	return true;
}

void GameLogic::addBonusBirdToList(PowerUpType_t powID, Bird* &bird) {
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