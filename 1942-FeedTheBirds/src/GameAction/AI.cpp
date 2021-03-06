﻿#include "..\..\include\GameAction\AI.h"

AI::AI(GameLogic *_gameLogic, FrameRangeAnimator* _flyAnimator, FrameRangeAnimation *_flyAnimation):
			gameLogic(_gameLogic),
			flyAnimator(_flyAnimator),
			flyAnimation(_flyAnimation) {
	lastUsedID = BASE_ID;
	
	smallBirds  = new std::vector<MovingPathAnimator*>;
	mediumBirds = new std::vector<MovingPathAnimator*>;
	largeBirds  = new std::vector<MovingPathAnimator*>;
		
	bonusBirds  = new std::vector<MovingPathAnimator*>;

	birdPathAnimator = new MovingPathAnimator();

	smallGreenBirdAnimation = this->createSmallGreenBirdAnimation();
	smallGreenBirdAnimationFromAbove = this->createSmallGreenBirdAnimationFromAbove();
	smallBlueBirdAnimationFromAbove = this->createSmallBlueBirdAnimationFromAbove();
	smallYellowBirdAnimationFromAbove = this->createSmallYellowBirdAnimationFromAbove();
	smallBlueBirdAnimation = this->createSmallBlueBirdAnimation();
	smallRedBirdAnimation = this->createSmallRedBirdAnimation();
	smallYellowBirdAnimation = this->createSmallYellowBirdAnimation();
	smallGreenGreyBirdAnimation = this->createSmallGreenGreyBirdAnimation();
	smallBlueGreyBirdAnimation = this->createSmallBlueGreyBirdAnimation();
	smallYellowGreyBirdAnimation = this->createSmallYellowGreyBirdAnimation();

	mediumGreenBirdAnimation = this->createMediumGreenBirdAnimation();
	mediumBrownBirdAnimation = this->createMediumBrownBirdAnimation();
	mediumYellowBirdFromBelowAnimation = this->createMediumYellowBirdFromBelowAnimation();
	mediumYellowBirdFromAboveAnimation = this->createMediumYellowBirdFromAboveAnimation();

	bigBirdAnimation = this->createBigBirdAnimation();

	followers = new std::vector<MovingAnimator*>;
	loopers = new std::vector<MovingPathAnimator*>;

	/* initialize random seed: */
	srand(time(NULL));
}

AI::~AI() {
	if (smallBirds) delete smallBirds;
	if (mediumBirds) delete mediumBirds;
	if (largeBirds) delete largeBirds;
	if (bonusBirds) delete bonusBirds;
}

void AI::cleanUp() {
	if (smallBirds->size()!=0) delete smallBirds;
	if (mediumBirds->size() != 0) delete mediumBirds;
	if (largeBirds->size() != 0) delete largeBirds;
	if (bonusBirds->size() != 0) delete bonusBirds;
}


void AI::eventAtX(int x)
{
	handleLittleBirds();
	handleMediumBirds();
	handleBoss();

	switch (x) {
	case 50:
		// action point for small birds
		addSmallBirds();
		break;
	//case 100:
	//	// action points for medium birds
	//	addMediumBirds();
	//	break;
	case 150:
		// action points for medium birds
		addMediumBirds();
		break;
	/*case 200:
		// action points for medium birds
		addSmallBirds();
		break;
	*/
	case 250:
		// action points for medium birds
		addSmallBirds();
		break;

	//case 300:
	//	// action points for medium birds
	//	addSmallBirds();
	//	break;

	case 350:
		// action points for medium birds
		addSmallBirds();
		break;

	//case 400:
	//	// action points for medium birds
	//	addMediumBirds();
	//	break;

	case 450:
		// action points for medium birds
		addSmallBirds();
		break;

	/*case 500:
		// action points for medium birds
		addSmallBirds();
		break;
		*/

	//POWER UP action point: 1000 points ! ! POW7
	case 520:
		addBonusBird(noEnemyBullets);
		break;
	case 540:
		addBonusBird(noEnemyBullets);
		break;
	case 560:
		addBonusBird(noEnemyBullets);
		break;
	case 580:
		addBonusBird(noEnemyBullets);
		break;
	case 600:
		addBonusBird(noEnemyBullets);
		gameLogic->checkNoEnemyBullets = true;
		break;

	case 550:
		// action points for medium birds
		addMediumBirds();
		break;

	/*case 570:
		// action points for medium birds
		addSmallBirds();
		break;
	*/
	case 650:
		// action points for medium birds
		addSmallBirds();
		break;

	/*case 650:
		// action points for medium birds
		addMediumBirds();
		break;
*/
	case 750:
		// action points for medium birds
		addSmallBirds();
		break;
/*
	case 750:
		// action points for medium birds
		addSmallBirds();
		break;
*/
	/*case 800:
		// action points for medium birds
		addMediumBirds();
		break;*/

	case 850:
		// action points for medium birds
		addSmallBirds();
		break;

/*	case 900:
		// action points for medium birds
		addMediumBirds();
		break;
*/
	case 950:
		// action points for medium birds
		addSmallBirds();
		break;
/*
	case 1050:
		// action points for medium birds
		addMediumBirds();
		break;
*/

	//POWER UP action point for QuadGun ! ! ! POW1
	case 1020:
		addBonusBird(quadGun);
		break;
	case 1040:
		addBonusBird(quadGun);
		break;
	case 1060:
		addBonusBird(quadGun);
		break;
	case 1080:
		addBonusBird(quadGun);
		break;
	case 1100:
		addBonusBird(quadGun);
		gameLogic->checkQuadGun = true;
		break;

	case 1150:
		// action points for medium birds
		addSmallBirds();
		break;
/*
	case 1150:
		// action points for medium birds
		addMediumBirds();
		break;
*/
	case 1250:
		// action points for medium birds
		addSmallBirds();
		break;
/*
	case 1250:
		// action points for medium birds
		addMediumBirds();
		break;
*/
/*
	case 1310:
		// action points for medium birds
		addSmallBirds();
		break;
*/
	case 1350:
		// action points for medium birds
		addSmallBirds();
		break;
/*
	case 1400:
		// action points for medium birds
		addMediumBirds();
		break;
*/
	case 1450:
		// action points for medium birds
		addSmallBirds();
		break;
		/*
	case 1500:
		// action points for medium birds
		addMediumBirds();
		break;
		*/

	//POWER UP action point: extra life! ! POW4
	case 1520:
		addBonusBird(points1000);
		break;
	case 1540:
		addBonusBird(points1000);
		break;
	case 1560:
		addBonusBird(points1000);
		break;
	case 1580:
		addBonusBird(points1000);
		break;
	case 1600:
		addBonusBird(points1000);
		gameLogic->check1000Points = true;
		break;

	//case 1600:
	//	// action points for medium birds
	//	addSmallBirds();
	//	break;

	case 1650:
		// action points for medium birds
		addMediumBirds();
		break;

	//case 1700:
	//	// action points for medium birds
	//	addSmallBirds();
	//	break;

	case 1750:
		addSmallBirds();
		break;  
/*
	case 1800:
		addSmallBirds();
		break;*/

	case 1850:
		addSmallBirds();
		break;
/*
	case 1900:
		addSmallBirds();
		break;
*/
	case 1950:
		addSmallBirds();
		break;
/*
	case 2000:
		addMediumBirds();
		break;*/
	//POWER UP action point: enemy crash ! ! ! POW2
	case 2020:
		addBonusBird(extraLife);
		break;
	case 2040:
		addBonusBird(extraLife);
		break;
	case 2060:
		addBonusBird(extraLife);
		break;
	case 2080:
		addBonusBird(extraLife);
		break;
	case 2100:
		addBonusBird(extraLife);
		gameLogic->checkExtraLife = true;
		break;

/*
	case 2100:
		addMediumBirds();
		break;*/

	case 2150:
		addMediumBirds();
		break;
/*
	case 2200:
		addSmallBirds();
		break;
*/
	case 2250:
		addMediumBirds();
		break;
/*
	case 2300:
		addSmallBirds();
		break;*/

	

	case 2410:
		addSmallBirds();
		break;
/*
	case 2460:
		addMediumBirds();
		break;
*/
	case 2500:
		// action point for boss
		this->addBoss(-10, 400,
			"bigBird",
			ColoredBossLives,
			ColoredBossSpeed,
			bigBirdAnimation);
		break;
/*
	case 2560:
		addSmallBirds();
		break;*/

	case 2600:
		addMediumBirds();
		break;
/*
	case 2660:
		addSmallBirds();
		break;
*/
	case 2700:
		addSmallBirds();
		break;
/*
	case 2760:
		addMediumBirds();
		break;*/

	case 2800:
		addSmallBirds();
		break;

	case 2900:
		addSmallBirds();
		break;

	//POWER UP action point: SIDE FIGHTERS ! ! POW3
	case 3020:
		addBonusBird(enemyCrash);
		break;
	case 3040:
		addBonusBird(enemyCrash);
		break;
	case 3060:
		addBonusBird(enemyCrash);
		break;
	case 3080:
		addBonusBird(enemyCrash);
		break;
	case 3100:
		addBonusBird(enemyCrash);
		gameLogic->checkEnemyCrash = true;
		break;

/*
	case 3060:
		addSmallBirds();
		break;*/

	case 3150:
		addMediumBirds();
		break;
/*
	case 3200:
		addSmallBirds();
		break;
*/
	case 3250:
		addMediumBirds();
		break;
/*
	case 3300:
		addMediumBirds();
		break;
*/
	case 3350:
		addSmallBirds();
		break;
/*
	case 3400:
		addSmallBirds();
		break;*/

	case 3450:
		addMediumBirds();
		break;
/*
	case 3500:
		addSmallBirds();
		break;
*/
	case 3550:
		addMediumBirds();
		break;
/*
	case 3600:
		addSmallBirds();
		break;*/

	case 3650:
		addMediumBirds();
		break;
/*
	case 3800:
		addSmallBirds();
		break;*/

	case 3750:
		addMediumBirds();
		break;
/*
	case 3900:
		addSmallBirds();
		break;*/

	case 3850:
		addSmallBirds();
		break;

	case 3950:
		addSmallBirds();
		break;

	//POWER UP action point: extra loop ! ! POW6
	case 4020:
		addBonusBird(extraLoop);
		break;
	case 4040:
		addBonusBird(extraLoop);
		break;
	case 4060:
		addBonusBird(extraLoop);
		break;
	case 4080:
		addBonusBird(extraLoop);
		break;
	case 4100:
		addBonusBird(extraLoop);
		gameLogic->checkExtraLoop = true;
		break;

/*
	case 4150:
		addSmallBirds();
		break;*/

	case 4200:
		addSmallBirds();
		break;
/*
	case 4300:
		addSmallBirds();
		break;*/

	case 4300:
		addMediumBirds();
		break;
/*
	case 4400:
		addSmallBirds();
		break;*/

/*	case 4750:
		addMediumBirds();
		break;*/
/*
	case 4800:
		addSmallBirds();
		break;
*/
	//POWER UP action point: extra life
	case 4310:
		addBonusBird(sideFighters);
		break;
	case 4330:
		addBonusBird(sideFighters);
		break;
	case 4350:
		addBonusBird(sideFighters);
		break;
	case 4370:
		addBonusBird(sideFighters);
		break;
	case 4390:
		addBonusBird(sideFighters);
		gameLogic->checkSideFighter = true;
		break;

	case 4550:
		// action point for boss
		this->addBoss(-10, 400,
					"bigBirdGrey",
					ColoredBossLives,
					ColoredBossSpeed,
					bigBirdAnimation);
		break;

	//-----------------------------------------------------------------
	case 5700:
		gameLogic->superAce->startLanding();
		break;

	default:
		break;
	}
}

Point* AI::getRandomEntryPoint() {
	Point* p = new Point();
	float randomEntryX, randomEntryY;
	randomEntryX = ((float)(rand() % 5 + 5) / 10)*SCREEN_WINDOW_WIDTH;
	randomEntryY = rand() % 2;
	if (randomEntryY == 0) {
		randomEntryY = SCREEN_WINDOW_HEIGHT + 10;
	}
	else {
		randomEntryY = -10;
	}
	p->setPoint(randomEntryX, randomEntryY);
	//cout << "Entry point: x=" << p->x << " y=" << p->y << "\n";
	return p;
}

void AI::makeBirdFollowSuperAce(Bird * bird, int loops)
{
	MovingAnimator *mar = new MovingAnimator();
	MovingAnimation * man = new MovingAnimation(0, (gameLogic->superAce->getY() - bird->getY()) > 0 ? 1: -1, bird->getBirdSpeed(), true, lastUsedID++);
	AnimatorHolder::markAsRunning(mar);
	this->followers->push_back(mar);
	mar->start(bird, man, getCurrTime());
	bird->setFollowsSuperAce(false);

	this->loopers->push_back(new MovingPathAnimator());
	this->loopers->back()->setHandleFrames(false);
	AnimatorHolder::markAsRunning(this->loopers->back());
	
	this->loopers->back()->start(bird, createLooperAnimation(loops), getCurrTime());
}

void AI::makeBirdShoot(Bird * bird)
{
	if (
		bird->getShotsRemaining()>0 &&
		(bird->getY() >= gameLogic->superAce->getY()*0.9) &&
		(bird->getY() <= gameLogic->superAce->getY()*1.1) &&
		!(rand() % 11)
		)//Bird is within 20% of superAce's y
	{
		BirdDropping* dropping = bird->shoot();
		if (!dropping) return;
		bird->decrFire();
		CollisionChecker::getInstance()->
			registerCollisions(gameLogic->superAce, dropping);
	}
}

MovingPathAnimation* AI::createLooperAnimation(int loops) {
	std::list<PathEntry> paths;
	std::list<PathEntry> path= *createCircularPath(SCREEN_WINDOW_HEIGHT*0.2, 270, 630, mediumColoredBirdSpeed);
	for (int i = 0; i < loops; i++) {
		paths.insert(paths.end(), path.begin(), path.end());
	}
	return new MovingPathAnimation(paths, lastUsedID++);
}

//------------------------ Boss Birds --------------------------------------------------

void AI::handleBoss() {
	Bird* bird;
	for (auto it = this->largeBirds->begin(); it != this->largeBirds->end(); it++)
	{
		bird = (Bird*)(*it)->getSprite();
		if (!bird->isDead()) {
			/*if ((*it)->hasFinished()) {
				bird->scare();
			}*/
			if (
				(bird->getY() >= gameLogic->superAce->getY()*0.7) &&
				(bird->getY() <= gameLogic->superAce->getY()*1.3) &&
				!(rand() % 31)
				)//Bird is within 20% of superAce's y
			{
				DROPPINGS* droppings = bird->bossShoot();
				if (!droppings) return;
				AudioHolder::changeToSound("shoot");
				//bird->decrFire();
				for (auto dr = droppings->begin(); dr != droppings->end(); dr++)
				{
					CollisionChecker::getInstance()->
						registerCollisions(gameLogic->superAce, *dr);
				}
			}
		}
	} 
}

void AI::addBoss(int x, int y, char* filmId, BirdLives lives, BirdSpeed speed, MovingPathAnimation* visVitalis) {
	this->largeBirds->push_back(birdPathAnimator->clone());
	this->largeBirds->back()->setHandleFrames(false);
	AnimatorHolder::markAsRunning(this->largeBirds->back());

	MovingPathAnimation* visVitalisCloned = visVitalis->clone(lastUsedID++);

	this->largeBirds->back()->start(gameLogic->createBird(x, y,
		bossBird,
		lives,
		speed, // TODO: TO BE USED on AI!
		bossBirdFire,
		filmId,
		flyAnimation->clone(lastUsedID++),
		flyAnimator->clone()),
		visVitalisCloned,
		getCurrTime());
}

MovingPathAnimation* AI::createBigBirdAnimation() {
	std::list<PathEntry> paths;
	paths.splice(paths.end(), *createSmoothDiagonalPath(100, 0, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(100, 0, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(100, 0, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(100, 0, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(100, 0, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(100, 0, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(100, 0, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(100, 0, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(100, 0, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(0, -100, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(0, -100, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(0, -100, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(0, -100, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(0, 0, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(0, 0, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(0, 0, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(0, 0, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(0, 0, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(0, 0, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(0, 100, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(0, 100, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(0, 100, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(0, 100, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(0, -100, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(0, -100, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(0, -100, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(0, -100, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(0, 0, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(0, 0, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(0, 0, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(0, 0, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(0, 0, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(0, 0, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(0, 100, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(0, 100, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(0, 100, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(0, 100, ColoredBossSpeed));
	return new MovingPathAnimation(paths, lastUsedID++);
}

//------------------------ Medium Birds ------------------------------------------------

// We need to generate medium birds that either:
// go on circles and approach super ace (brown)
// come from the side and attack ()
// 
// in every run we use a rand to generate a different case
void AI::addMediumBirds(void) {

	// generate secret number between 1 and 4
	// used to generate different kind of medium bird
	int iSecret = rand() % 4 + 1;

	if (iSecret == 1) {
		// Green Medium Bird
		
		this->addMediumBird(SCREEN_WINDOW_WIDTH*0.75,
							SCREEN_WINDOW_HEIGHT + 10,
							"mediumGreenBird",
							mediumColoredBirdLives,
							mediumColoredBirdSpeed,
							mediumGreenBirdAnimation, 0);
		
	}
	else if (iSecret == 2) {
		// Yellow Medium Bird

		this->addMediumBird(SCREEN_WINDOW_WIDTH*0.75,
							0,
							"mediumYellowBird",
							mediumColoredBirdLives,
							mediumColoredBirdSpeed,
							mediumYellowBirdFromAboveAnimation, 0);

		this->addMediumBird(SCREEN_WINDOW_WIDTH*0.75 - 100,
							-50,
							"mediumYellowBird",
							mediumColoredBirdLives,
							mediumColoredBirdSpeed,
							mediumYellowBirdFromAboveAnimation, 0);

		this->addMediumBird(SCREEN_WINDOW_WIDTH*0.75 - 200,
							-100,
							"mediumYellowBird",
							mediumColoredBirdLives,
							mediumColoredBirdSpeed,
							mediumYellowBirdFromAboveAnimation, 0);
		/*
		this->addMediumBird(SCREEN_WINDOW_WIDTH*0.75,
							SCREEN_WINDOW_HEIGHT,
							"mediumYellowBird",
							mediumColoredBirdLives,
							mediumColoredBirdSpeed,
							mediumYellowBirdFromBelowAnimation, 0); 
			SCREEN_WINDOW_HEIGHT - 50,
			"mediumYellowBird",
			mediumColoredBirdLives,
			mediumColoredBirdSpeed,
			mediumYellowBirdFromBelowAnimation, 0);
		//this->addMediumBird(SCREEN_WINDOW_WIDTH*0.75 - 200,
		//	-100,
		//	"mediumYellowBird",
		//	mediumColoredBirdLives,
		//	mediumColoredBirdSpeed,
		//	mediumYellowBirdFromAboveAnimation, 0);
		//this->addMediumBird(SCREEN_WINDOW_WIDTH*0.75 - 200,
		//	SCREEN_WINDOW_HEIGHT - 100,
		//	"mediumYellowBird",
		//	mediumColoredBirdLives,
		//	mediumColoredBirdSpeed,
		//	mediumYellowBirdFromBelowAnimation, 0);
		
		this->addMediumBird(SCREEN_WINDOW_WIDTH*0.75 - 100,
							SCREEN_WINDOW_HEIGHT - 50,
							"mediumYellowBird",
							mediumColoredBirdLives,
							mediumColoredBirdSpeed,
							mediumYellowBirdFromBelowAnimation, 0);

		this->addMediumBird(SCREEN_WINDOW_WIDTH*0.75 - 200,
							SCREEN_WINDOW_HEIGHT - 100,
							"mediumYellowBird",
							mediumColoredBirdLives,
							mediumColoredBirdSpeed,
							mediumYellowBirdFromBelowAnimation, 0);
		*/
	}
	else if (iSecret == 3) {
		// Brown Medium Birds
		this->addMediumBird(SCREEN_WINDOW_WIDTH - 300,
			SCREEN_WINDOW_HEIGHT / 2,
			"mediumBrownBird",
			mediumColoredBirdLives,
			mediumColoredBirdSpeed,
			mediumBrownBirdAnimation,
			5);
	}
	else if (iSecret == 4) {
		// Grey Medium Birds
		
		this->addMediumBird(SCREEN_WINDOW_WIDTH,
			SCREEN_WINDOW_HEIGHT / 2,
			"mediumBrownBird",
			mediumColoredBirdLives,
			mediumColoredBirdSpeed,
			mediumBrownBirdAnimation, 0);
		
	}

}

void AI::handleMediumBirds() {
	Bird* bird;
	for (auto it = this->mediumBirds->begin(); it != this->mediumBirds->end(); )
	{
		bird = (Bird*)(*it)->getSprite();
		if (!bird->isDead()) {
			if ((*it)->hasFinished() && (bird->getFollowsSuperAce())) {
				makeBirdFollowSuperAce(bird, bird->getFollowsSuperAce());
				it = this->mediumBirds->erase(it);
			}
			else if ((*it)->hasFinished()) {
				bird->scare();
				it = this->mediumBirds->erase(it);
			}
			else {
				makeBirdShoot(bird);
				it++;
			}
		}
		else {
			(*it)->stop();
			it=this->mediumBirds->erase(it);
		}
	}
	for (auto it = this->followers->begin(); it != this->followers->end();) {
		bird = (Bird*)(*it)->getSprite();
		if (!bird->isDead()) {
			(*it)->getAnimation()->setDx(0);
			(*it)->getAnimation()->setDy((gameLogic->superAce->getY() - bird->getY()) > 0 ? 1 : -1);
			makeBirdShoot(bird);
			it++;
		}
		else {
			(*it)->stop();
			it = this->followers->erase(it);
		}
		//it++;
	}
	for (auto it = this->loopers->begin(); it != this->loopers->end();) {
		bird = (Bird*)(*it)->getSprite();
		if ((*it)->hasFinished()) {
			bird->scare();
			it=this->loopers->erase(it);
		}
		else {
			it++;
		}
	}
}

void AI::addMediumBird(int x, int y, char* filmId, BirdLives lives, BirdSpeed speed, MovingPathAnimation* visVitalis, int followsSuperAce) {

	this->mediumBirds->push_back(birdPathAnimator->clone());
	this->mediumBirds->back()->setHandleFrames(false);
	AnimatorHolder::markAsRunning(this->mediumBirds->back());

	MovingPathAnimation* visVitalisCloned = visVitalis->clone(lastUsedID++);

	this->mediumBirds->back()->start(gameLogic->createBird(x, y,
														mediumBird,
														lives,
														speed, // TODO: TO BE USED on AI!
														mediumBirdFire,
														filmId,
														flyAnimation->clone(lastUsedID++),
														flyAnimator->clone()),
									visVitalisCloned,
									getCurrTime());
	((Bird*)this->mediumBirds->back()->getSprite())->setFollowsSuperAce(followsSuperAce);
}

// create a Brown Medium Bird
// apo to panw meros ths othonis kanoun ena kuklo k sunexizoun na mas vroun
MovingPathAnimation* AI::createMediumBrownBirdAnimation() {
	std::list<PathEntry> paths;
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.10, 90, 360, mediumColoredBirdSpeed));
	return new MovingPathAnimation(paths, lastUsedID++);
}

// apo to katw meros ki anevainoun
MovingPathAnimation* AI::createMediumGreenBirdAnimation() {
	std::list<PathEntry> paths;
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_HEIGHT*0.20, 180, 360, mediumColoredBirdSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(-60, -100, mediumColoredBirdSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(-60, -SCREEN_WINDOW_HEIGHT*0.20, mediumColoredBirdSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(-60, -SCREEN_WINDOW_WIDTH*0.20, mediumColoredBirdSpeed));
	return new MovingPathAnimation(paths, lastUsedID++);
}

// se smhnos (ki ap tis 2 pleures) 
MovingPathAnimation* AI::createMediumYellowBirdFromAboveAnimation() {
	std::list<PathEntry> paths;
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_HEIGHT*0.25, 0, 180, mediumColoredBirdSpeed*4));
	paths.splice(paths.end(), *createSmoothDiagonalPath(-SCREEN_WINDOW_WIDTH, 0, mediumColoredBirdSpeed));
	return new MovingPathAnimation(paths, lastUsedID++);
}

MovingPathAnimation* AI::createMediumYellowBirdFromBelowAnimation() {
	std::list<PathEntry> paths;
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_HEIGHT*0.25, 180, 360, mediumColoredBirdSpeed*4));
	paths.splice(paths.end(), *createSmoothDiagonalPath(-SCREEN_WINDOW_WIDTH, 0, mediumColoredBirdSpeed));
	return new MovingPathAnimation(paths, lastUsedID++);
}

// idia kinisi apla me megalutero speed
MovingPathAnimation* AI::createMediumGreyBirdAnimation() {
	std::list<PathEntry> paths;
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.25, 0, 180, mediumGreyBirdSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(-SCREEN_WINDOW_WIDTH, 0, mediumGreyBirdSpeed));
	return new MovingPathAnimation(paths, lastUsedID++);
}

//------------------------ Bonus Birds --------------------------------------------------

void AI::addBonusBird(PowerUpType_t powID)
{
	this->addBonusBird(powID,
						SCREEN_WINDOW_WIDTH*0.75 + 100,
						SCREEN_WINDOW_HEIGHT + 200,
						"smallRedBird",
						smallRedBirdAnimation);
	
}

void AI::addBonusBird(PowerUpType_t powID, int x, int y, char* filmId, MovingPathAnimation* visVitalis)
{
	this->bonusBirds->push_back(birdPathAnimator->clone());
	this->bonusBirds->back()->setHandleFrames(false);
	AnimatorHolder::markAsRunning(this->bonusBirds->back());

	// create a bonus bird on logic instance
	Bird* bird = gameLogic->createBird(x, y,
										bonusBird,
										littleBirdLives,
										littleBirdSpeed,
										littleBirdFire,
										filmId,
										flyAnimation->clone(lastUsedID++),
										flyAnimator->clone());
	// update bonus birds list on Game Logic
	gameLogic->addBonusBirdToList(powID, bird);

	this->bonusBirds->back()->start(bird, visVitalis->clone(lastUsedID++), getCurrTime());
}

//------------------------ Small Birds --------------------------------------------------

void AI::addSmallBirds() {
	// Action point for small birds

	// Generate secret number between 1 and 8
	// used to generate different kind of medium bird
	int iRandomBird = rand() % 8 + 1;

	switch (iRandomBird) {
	case 1:
		addBlueSmallBird();
		break;
	case 2:
		addGreenSmallBird();
		break;
	case 3:
		addYellowSmallBird();
		break;
	case 4:
		addBlueGreySmallBird();
		break;
	case 5:
		addGreenGreySmallBird();
		break;
	case 6:
		addBlueGreySmallBird();
		break;
	case 7:
		addYellowGreySmallBird();
		break;
	case 8:
		addYellowGreySmallBird();
		break;
	default:
		break;
	}
}

void AI::addGreenSmallBird() {
	Point* randomEntryPoint;
	randomEntryPoint = getRandomEntryPoint();
	MovingPathAnimation* anim;
	if (randomEntryPoint->y < 0) {
		anim = smallGreenBirdAnimationFromAbove->clone(lastUsedID++);
	}
	else {
		anim = smallGreenBirdAnimation->clone(lastUsedID++);
	}
	this->addSmallBird(randomEntryPoint->x,
		randomEntryPoint->y,
		"smallGreenBird",
		anim, 0);
}

void AI::addBlueSmallBird() {
	Point* randomEntryPoint;
	randomEntryPoint = getRandomEntryPoint();
	MovingPathAnimation* anim;
	if (randomEntryPoint->y < 0) {
		anim = smallBlueBirdAnimationFromAbove->clone(lastUsedID++);
	}
	else {
		anim = smallBlueBirdAnimation->clone(lastUsedID++);
	}
	this->addSmallBird(randomEntryPoint->x,
		randomEntryPoint->y,
		"smallBlueBird",
		anim, 0);
}

void AI::addYellowSmallBird() {
	Point* randomEntryPoint;
	randomEntryPoint = getRandomEntryPoint();
	MovingPathAnimation* anim;
	if (randomEntryPoint->y < 0) {
		anim = smallYellowBirdAnimationFromAbove->clone(lastUsedID++);
	}
	else {
		anim = smallYellowBirdAnimation->clone(lastUsedID++);
	}
	this->addSmallBird(randomEntryPoint->x,
		randomEntryPoint->y,
		"smallYellowBird",
		anim, 0);
}

void AI::addGreenGreySmallBird() {
	float randomEntryY = ((float)(rand() % 5) / 10)*SCREEN_WINDOW_HEIGHT;
	this->addSmallBird(SCREEN_WINDOW_WIDTH,
		randomEntryY,
		"smallGreenBirdGrey",
		smallGreenGreyBirdAnimation, 0);
}

void AI::addBlueGreySmallBird() {
	float randomEntryY = ((float)(rand() % 5+5) / 10)*SCREEN_WINDOW_HEIGHT;
	this->addSmallBird(SCREEN_WINDOW_WIDTH,
		randomEntryY,
		"smallBlueBirdGrey",
		smallBlueGreyBirdAnimation, 0);
}

void AI::addYellowGreySmallBird() {
	this->addSmallBird(SCREEN_WINDOW_WIDTH,
		300,
		"smallYellowBirdGrey",
		smallYellowGreyBirdAnimation, 0);
}


void AI::addSmallBird(int x, int y, char* filmId, MovingPathAnimation* visVitalis, int followsSuperAce) {
	this->smallBirds->push_back(birdPathAnimator->clone());
	this->smallBirds->back()->setHandleFrames(false);
	AnimatorHolder::markAsRunning(this->smallBirds->back());

	MovingPathAnimation* visVitalisCloned = visVitalis->clone(lastUsedID++);

	this->smallBirds->back()->start(
									gameLogic->createBird(x, y,
										littleBird,
										littleBirdLives,
										littleBirdSpeed, // TODO: TO BE USED on AI!
										littleBirdFire,
										filmId,
										flyAnimation->clone(lastUsedID++),
										flyAnimator->clone()),
									visVitalisCloned,
									getCurrTime());
	((Bird*)this->smallBirds->back()->getSprite())->setFollowsSuperAce(followsSuperAce);
}

void AI::handleLittleBirds()
{
	Bird* bird;
	for (auto it = this->smallBirds->begin(); it != this->smallBirds->end(); it++)
	{
		bird = (Bird*)(*it)->getSprite();
		if (!bird->isDead()) {
			if ((*it)->hasFinished()) {
				bird->scare();
			}
			else
				makeBirdShoot(bird);
		}
	}
}

//erxontai apo katw, kanoun tyxaious kykloys kai feygoyn
MovingPathAnimation* AI::createSmallGreenBirdAnimation() {
	std::list<PathEntry> paths;
	//todo appropriately
	
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.20, 180, 360, littleBirdSpeed));
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.10, 180, 720, littleBirdSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(-100, -100, littleBirdSpeed));
	return new MovingPathAnimation(paths, lastUsedID++);
}

//erxontai apo panw, kanoun tyxaious kykloys kai feygoyn
MovingPathAnimation* AI::createSmallGreenBirdAnimationFromAbove() {
	std::list<PathEntry> paths;
	//todo appropriately

	paths.splice(paths.end(), *createSmoothDiagonalPath(10, 200, littleBirdSpeed));
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.20, 180, 360, littleBirdSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(-300, 0, littleBirdSpeed));
	//paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.10, 180, 720, littleBirdSpeed));
	return new MovingPathAnimation(paths, lastUsedID++);
}

//kanoun perissoterous kukloys
MovingPathAnimation* AI::createSmallBlueBirdAnimation() {
	std::list<PathEntry> paths;
	//todo appropriately
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.20, 180, 360, littleBirdSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(-100, -10, littleBirdSpeed));
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.15, 180, 720, littleBirdSpeed));
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.14, 180, 360, littleBirdSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(-100, -100, littleBirdSpeed));
	return new MovingPathAnimation(paths, lastUsedID++);
}

MovingPathAnimation* AI::createSmallBlueBirdAnimationFromAbove() {
	std::list<PathEntry> paths;
	//todo appropriately
	paths.splice(paths.end(), *createSmoothDiagonalPath(0, 200, littleBirdSpeed));
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.20, 180, 360, littleBirdSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(200, 10, littleBirdSpeed));
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.15, 180, 720, littleBirdSpeed));
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.14, 180, 360, littleBirdSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(100, -10, littleBirdSpeed));
	return new MovingPathAnimation(paths, lastUsedID++);
}

//bonus bird
MovingPathAnimation* AI::createSmallRedBirdAnimation() {
	std::list<PathEntry> paths; 
	paths.splice(paths.end(), *createSmoothDiagonalPath(0, -200, littleBirdSpeed));
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.15, 180, 360, littleBirdSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(-100, -100, littleBirdSpeed));
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.17, 180, 720, littleBirdSpeed));
	return new MovingPathAnimation(paths, lastUsedID++);
}

//megalyteres kampyles, apeutheias epitheseis
MovingPathAnimation* AI::createSmallYellowBirdAnimation() {
	std::list<PathEntry> paths;
	paths.splice(paths.end(), *createSmoothDiagonalPath(-200, -100, littleBirdSpeed));
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.30, 180, 360, littleBirdSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(-100, 5, littleBirdSpeed));
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.20, 180, 270, littleBirdSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(-100, -100, littleBirdSpeed));
	return new MovingPathAnimation(paths, lastUsedID++);
}

MovingPathAnimation* AI::createSmallYellowBirdAnimationFromAbove() {
	std::list<PathEntry> paths;
	paths.splice(paths.end(), *createSmoothDiagonalPath(0, 300, littleBirdSpeed));
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.30, 180, 360, littleBirdSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(-100, 5, littleBirdSpeed));
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.20, 180, 270, littleBirdSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(-300, -100, littleBirdSpeed));
	return new MovingPathAnimation(paths, lastUsedID++);
}

//erxontai katheta (apo ta deksia) kai sto telos plisiazoun ton SuperAce
//erxontai diagwnia pros ton superAce kai otan plisiasoun apomakrynontai
MovingPathAnimation* AI::createSmallGreenGreyBirdAnimation() {
	std::list<PathEntry> paths;
	paths.splice(paths.end(), *createSmoothDiagonalPath(-400, 0, littleGreyBirdSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(-400, 40, littleGreyBirdSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(-100, 0, littleGreyBirdSpeed));
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.17, 180, 360, littleBirdSpeed));
	return new MovingPathAnimation(paths, lastUsedID++);
}

MovingPathAnimation* AI::createSmallBlueGreyBirdAnimation() {
	std::list<PathEntry> paths;
	paths.splice(paths.end(), *createSmoothDiagonalPath(-600, 0, littleBirdSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(-500, -20, littleBirdSpeed));
	//.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.17, 180, 720, littleBirdSpeed));
	return new MovingPathAnimation(paths, lastUsedID++);
}

MovingPathAnimation* AI::createSmallYellowGreyBirdAnimation() {
	std::list<PathEntry> paths;
	paths.splice(paths.end(), *createSmoothDiagonalPath(-600, 10, littleBirdSpeed));
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.20, 180, 360, littleBirdSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(-400, -100, littleBirdSpeed));
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.17, 180, 720, littleBirdSpeed));
	return new MovingPathAnimation(paths, lastUsedID++);
}