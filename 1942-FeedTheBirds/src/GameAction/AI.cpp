#include "..\..\include\GameAction\AI.h"

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
	delete smallBirds;
	delete mediumBirds;
	delete largeBirds;
	delete bonusBirds;
}

void AI::eventAtX(int x)
{
	handleLittleBirds();
	handleMediumBirds();
	handleBoss();

	cout << "X is " << x<< endl;
	switch (x) {
	case 30:
		// action point for small birds
		addSmallBirds();
		break;
	case 80:
		// action point for small birds
		addSmallBirds();
		break;
	case 100:
		// action points for medium birds
		addMediumBirds();
		break;
	case 150:
		// action points for medium birds
		addMediumBirds();
		break;

	case 200:
		// action points for medium birds
		addSmallBirds();
		addMediumBirds();
		break;

	//POWER UP action point for QuadGun ! ! ! POW1
	case 220:
		addBonusBird(quadGun);
		break;
	case 240:
		addBonusBird(quadGun);
		break;
	case 260:
		addBonusBird(quadGun);
		break;
	case 280:
		addBonusBird(quadGun);
		break;
	case 300:
		addBonusBird(quadGun);
		gameLogic->checkQuadGun = true;
		break;

	case 370:
		addSmallBirds();
		addMediumBirds();
		break;  

	case 470:
		addSmallBirds();
		addMediumBirds();
		break;
	case 570:
		addSmallBirds();
		addMediumBirds();
		break;

	case 1000:
		// action point for boss
		this->addBoss(-10, 400,
					  "bigBird",
					  ColoredBossLives,
					  ColoredBossSpeed,
					  bigBirdAnimation);
		break;

	//POWER UP action point: enemy crash ! ! ! POW2
	case 1520:
		addBonusBird(enemyCrash);
		break;
	case 1540:
		addBonusBird(enemyCrash);
		break;
	case 1560:
		addBonusBird(enemyCrash);
		break;
	case 1580:
		addBonusBird(enemyCrash);
		break;
	case 1600:
		addBonusBird(enemyCrash);
		gameLogic->checkEnemyCrash = true;
		break;

	//POWER UP action point: SIDE FIGHTERS ! ! POW3
	case 3020:
		addBonusBird(sideFighters);
		break;
	case 3040:
		addBonusBird(sideFighters);
		break;
	case 3060:
		addBonusBird(sideFighters);
		break;
	case 3080:
		addBonusBird(sideFighters);
		break;
	case 3100:
		addBonusBird(sideFighters);
		gameLogic->checkSideFighter = true;
		break;

	//POWER UP action point: extra life! ! POW4
	case 4520:
		addBonusBird(extraLife);
		break;
	case 4540:
		addBonusBird(extraLife);
		break;
	case 4560:
		addBonusBird(extraLife);
		break;
	case 4580:
		addBonusBird(extraLife);
		break;
	case 4600:
		addBonusBird(extraLife);
		gameLogic->checkExtraLife = true;
		break;

	//POWER UP action point: no enemies bullets! ! POW5
	case 5020:
		addBonusBird(noEnemyBullets);
		break;
	case 5040:
		addBonusBird(noEnemyBullets);
		break;
	case 5060:
		addBonusBird(noEnemyBullets);
		break;
	case 5080:
		addBonusBird(noEnemyBullets);
		break;
	case 5100:
		addBonusBird(noEnemyBullets);
		gameLogic->checkNoEnemyBullets = true;
		break;

	//POWER UP action point: extra loop ! ! POW6
	case 6620:
		addBonusBird(extraLoop);
		break;
	case 6640:
		addBonusBird(extraLoop);
		break;
	case 6660:
		addBonusBird(extraLoop);
		break;
	case 6680:
		addBonusBird(extraLoop);
		break;
	case 6700:
		addBonusBird(extraLoop);
		gameLogic->checkExtraLoop = true;
		break;

	//POWER UP action point: 1000 points ! ! POW7
	case 8020:
		addBonusBird(points1000);
		break;
	case 8040:
		addBonusBird(points1000);
		break;
	case 8060:
		addBonusBird(points1000);
		break;
	case 8080:
		addBonusBird(points1000);
		break;
	case 8100:
		addBonusBird(points1000);
		gameLogic->check1000Points = true;
		break;
	
	case 8800:
		// action point for boss
		this->addBoss(-10, 400,
					"bigBirdGrey",
					ColoredBossLives,
					ColoredBossSpeed,
					bigBirdAnimation);
		break;
	case 9400:	// TODO: change to terrain length minus something : P
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
	cout << "Entry point: x=" << p->x << " y=" << p->y << "\n";
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
		bird->decrFire();
		CollisionChecker::getInstance()->
			registerCollisions(gameLogic->superAce, dropping);
	}
}

MovingPathAnimation* AI::createLooperAnimation(int loops) {
	std::list<PathEntry> paths;
	std::list<PathEntry> path= *createCircularPath(SCREEN_WINDOW_HEIGHT*0.20, 270, 630, mediumColoredBirdSpeed);
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
				(bird->getY() >= gameLogic->superAce->getY()*0.9) &&
				(bird->getY() <= gameLogic->superAce->getY()*1.1) &&
				!(rand() % 11)
				)//Bird is within 20% of superAce's y
			{
				DROPPINGS* droppings = bird->bossShoot();
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
		this->addMediumBird(SCREEN_WINDOW_WIDTH*0.75,
			SCREEN_WINDOW_HEIGHT,
			"mediumYellowBird",
			mediumColoredBirdLives,
			mediumColoredBirdSpeed,
			mediumYellowBirdFromBelowAnimation, 0);
		this->addMediumBird(SCREEN_WINDOW_WIDTH*0.75 - 100,
			-50,
			"mediumYellowBird",
			mediumColoredBirdLives,
			mediumColoredBirdSpeed,
			mediumYellowBirdFromAboveAnimation, 0);
		this->addMediumBird(SCREEN_WINDOW_WIDTH*0.75 - 100,
			SCREEN_WINDOW_HEIGHT - 50,
			"mediumYellowBird",
			mediumColoredBirdLives,
			mediumColoredBirdSpeed,
			mediumYellowBirdFromBelowAnimation, 0);
		this->addMediumBird(SCREEN_WINDOW_WIDTH*0.75 - 200,
			-100,
			"mediumYellowBird",
			mediumColoredBirdLives,
			mediumColoredBirdSpeed,
			mediumYellowBirdFromAboveAnimation, 0);
		this->addMediumBird(SCREEN_WINDOW_WIDTH*0.75 - 200,
			SCREEN_WINDOW_HEIGHT - 100,
			"mediumYellowBird",
			mediumColoredBirdLives,
			mediumColoredBirdSpeed,
			mediumYellowBirdFromBelowAnimation, 0);
		
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
	for (auto it = this->followers->begin(); it != this->followers->end(); it++) {
		bird = (Bird*)(*it)->getSprite();
		if (!bird->isDead()) {
			(*it)->getAnimation()->setDx(0);
			(*it)->getAnimation()->setDy((gameLogic->superAce->getY() - bird->getY()) > 0 ? 1 : -1);
			makeBirdShoot(bird);
		}
		else {
			(*it)->stop();
			/*auto tmp = it;
			it--;
			this->followers->erase(tmp);*/
		}
	}
	for (auto it = this->loopers->begin(); it != this->loopers->end(); it++) {\
		if ((*it)->hasFinished()) {
			bird->scare();
			/*auto tmp = it;
			it--;
			this->loopers->erase(tmp);*/
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
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_HEIGHT*0.25, 0, 180, mediumColoredBirdSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(-SCREEN_WINDOW_WIDTH, 0, mediumColoredBirdSpeed/5));
	return new MovingPathAnimation(paths, lastUsedID++);
}

MovingPathAnimation* AI::createMediumYellowBirdFromBelowAnimation() {
	std::list<PathEntry> paths;
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_HEIGHT*0.25, 180, 360, mediumColoredBirdSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(-SCREEN_WINDOW_WIDTH, 0, mediumColoredBirdSpeed/5));
	return new MovingPathAnimation(paths, lastUsedID++);
}

// idia kinisi apla me megalutero speed
MovingPathAnimation* AI::createMediumGreyBirdAnimation() {
	std::list<PathEntry> paths;
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.25, 0, 180, mediumGreyBirdSpeed/3));
	paths.splice(paths.end(), *createSmoothDiagonalPath(-SCREEN_WINDOW_WIDTH, 0, mediumGreyBirdSpeed/3));
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

	MovingPathAnimation* visVitalisCloned = visVitalis->clone(lastUsedID++);

	this->bonusBirds->back()->start(bird, visVitalisCloned, getCurrTime());
}

//------------------------ Small Birds --------------------------------------------------

void AI::addSmallBirds() {
	// action point for small birds

	// generate secret number between 1 and 8
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