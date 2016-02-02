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
	smallBlueBirdAnimation = this->createSmallBlueBirdAnimation();
	smallRedBirdAnimation = this->createSmallRedBirdAnimation();
	smallYellowBirdAnimation = this->createSmallYellowBirdAnimation();

	mediumGreenBirdAnimation = this->createMediumGreenBirdAnimation();
	mediumBrownBirdAnimation = this->createMediumBrownBirdAnimation();
	mediumYellowBirdAnimation = this->createMediumYellowBirdAnimation();

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

	switch (x) {
	case 20:
		// action point for small birds
		addSmallBirds();
		break;
	case 100:
		// action points for medium birds
		addMediumBirds();
		break;
	case 120:
		// action points for side fighter
		gameLogic->superAce->fetchSideFighters();
		break;
	case 150:
		// action points for medium birds
		addMediumBirds();
		break;
	case 200:
		// action points for medium birds
		addMediumBirds();
		break;
	//next cases for 1st bonus: QuadGun ! ! !
	case 220:
		addBonusBirds();
		break;
	case 240:
		addBonusBirds();
		break;
	case 260:
		addBonusBirds();
		break;
	case 280:
		addBonusBirds();
		break;
	case 300:
		addBonusBirds();
		gameLogic->checkSideFighter = true;
		break;
	case 370:
		break;  
	case 500:

		// action point for boss
		this->addBoss(-10,
			400,
			"bigBird",
			ColoredBossLives,
			ColoredBossSpeed,
			bigBirdAnimation);
		break;
	case 3400:	// TODO: change to terrain length minus something : P
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
		!(rand() % 31)
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
				!(rand() % 31)
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
	paths.splice(paths.end(), *createSmoothDiagonalPath(100, -1, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(100, 0, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(100, -1, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(100, 0, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(100, -1, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(100, 0, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(100, -1, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(0, -100, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(0, -100, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(0, -100, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(0, 0, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(0, 0, ColoredBossSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(0, 0, ColoredBossSpeed));
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
	iSecret = 3; //TODO: just for debugging! ! !

	// random num of birds each time (max 5)
	int birdsNum = rand() % 5+1;	// TODO: to be used inside ifs

	if (iSecret == 1) {
		// Green Medium Bird
		/*
		this->addMediumBird(SCREEN_WINDOW_WIDTH*0.75,
		SCREEN_WINDOW_HEIGHT + 10,
		"mediumGreenBird",
		mediumColoredBirdLives,
		mediumColoredBirdSpeed,
		mediumGreenBirdAnimation);
		*/
	}
	else if (iSecret == 2) {
		// Yellow Medium Bird
		/*
		this->addMediumBird(SCREEN_WINDOW_WIDTH*0.75 + 50,
		SCREEN_WINDOW_HEIGHT + 60,
		"mediumYellowBird",
		mediumColoredBirdLives,
		mediumColoredBirdSpeed,
		mediumYellowBirdAnimation);
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
		/*
		this->addMediumBird(SCREEN_WINDOW_WIDTH,
			SCREEN_WINDOW_HEIGHT / 2,
			"mediumBrownBird",
			mediumColoredBirdLives,
			mediumColoredBirdSpeed,
			mediumBrownBirdAnimation);
		*/
	}

}

void AI::handleMediumBirds() {
	Bird* bird;
	for (auto it = this->mediumBirds->begin(); it != this->mediumBirds->end(); it++)
	{
		bird = (Bird*)(*it)->getSprite();
		if (!bird->isDead()) {
			if ((*it)->hasFinished() && (bird->getFollowsSuperAce())) {
				makeBirdFollowSuperAce(bird, bird->getFollowsSuperAce());
				/*auto tmp = it;
				it--;
				this->mediumBirds->erase(tmp);*/
			}
			else if ((*it)->hasFinished()) {
				bird->scare();
				/*auto tmp = it;
				it--;
				this->mediumBirds->erase(tmp);*/
			}
			else makeBirdShoot(bird);
		}
		else {
			(*it)->stop();
			/*auto tmp = it;
			it--;
			this->mediumBirds->erase(tmp);*/
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
	//paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.10, 360, 720, mediumColoredBirdSpeed));

	//paths.splice(paths.end(), *createSmoothDiagonalPath(SCREEN_WINDOW_WIDTH, 0, mediumColoredBirdSpeed));
	return new MovingPathAnimation(paths, lastUsedID++);
}

// apo to katw meros ki anevainoun
MovingPathAnimation* AI::createMediumGreenBirdAnimation() {
	std::list<PathEntry> paths;
	//todo appropriately
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.20, 180, 360, mediumColoredBirdSpeed));
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.10, 180, 720, mediumColoredBirdSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(-100, -100, mediumColoredBirdSpeed));
	return new MovingPathAnimation(paths, lastUsedID++);
}

// se smhnos (ki ap tis 2 pleures) 
MovingPathAnimation* AI::createMediumYellowBirdAnimation() {
	std::list<PathEntry> paths;
	//todo appropriately
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.20, 180, 360, mediumColoredBirdSpeed));
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.10, 180, 720, mediumColoredBirdSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(-100, -100, mediumColoredBirdSpeed));
	return new MovingPathAnimation(paths, lastUsedID++);
}

// idia kinisi apla me megalutero speed
MovingPathAnimation* AI::createMediumGreyBirdAnimation() {
	std::list<PathEntry> paths;
	//todo appropriately
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.20, 180, 360, mediumGreyBirdSpeed));
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.10, 180, 720, mediumGreyBirdSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(-100, -100, mediumGreyBirdSpeed));
	return new MovingPathAnimation(paths, lastUsedID++);
}

//------------------------ Bonus Birds --------------------------------------------------

void AI::addBonusBirds(void)
{
	this->addBonusBird(SCREEN_WINDOW_WIDTH*0.75 + 100,
						SCREEN_WINDOW_HEIGHT + 200,
						"smallRedBird",
						smallRedBirdAnimation);
	
}

void AI::addBonusBird(int x, int y, char* filmId, MovingPathAnimation* visVitalis) {
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
	//update bonus birds list on Game Logic
	gameLogic->bonusBirds->push_back(bird);

	MovingPathAnimation* visVitalisCloned = visVitalis->clone(lastUsedID++);

	this->bonusBirds->back()->start(bird, visVitalisCloned, getCurrTime());
}

//------------------------ Small Birds --------------------------------------------------

void AI::addSmallBirds() {
	// action point for small birds
	Point* randomEntryPoint;
	randomEntryPoint = getRandomEntryPoint();
	this->addSmallBird(randomEntryPoint->x,
		randomEntryPoint->y,
		"smallGreenBird",
		smallGreenBirdAnimation,0);
	randomEntryPoint = getRandomEntryPoint();
	this->addSmallBird(randomEntryPoint->x,
		randomEntryPoint->y,
		"smallYellowBird",
		smallYellowBirdAnimation,0);
	randomEntryPoint = getRandomEntryPoint();
	this->addSmallBird(randomEntryPoint->x,
		randomEntryPoint->y,
		"smallBlueBird",
		smallBlueBirdAnimation,0);  
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

//erxontai apo ta plagia, kanoun tyxaious kykloys kai feygoyn
MovingPathAnimation* AI::createSmallGreenBirdAnimation() {
	std::list<PathEntry> paths;
	//todo appropriately
	
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.20, 180, 360, littleBirdSpeed));
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.10, 180, 720, littleBirdSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(-100, -100, littleBirdSpeed));
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

//bonus bird
MovingPathAnimation* AI::createSmallRedBirdAnimation() {
	std::list<PathEntry> paths;
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.20, 180, 360, littleBirdSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(-100, -100, littleBirdSpeed));
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.17, 180, 720, littleBirdSpeed));
	return new MovingPathAnimation(paths, lastUsedID++);
}

//megalyteres kampyles, apeutheias epitheseis
MovingPathAnimation* AI::createSmallYellowBirdAnimation() {
	std::list<PathEntry> paths;
	//todo appropriately
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.30, 180, 360, littleBirdSpeed));
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.20, 180, 720, littleBirdSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(-100, -100, littleBirdSpeed));
	return new MovingPathAnimation(paths, lastUsedID++);
}

//erxontai katheta (apo ta deksia) kai sto telos plisiazoun ton SuperAce
//erxontai diagwnia pros ton superAce kai otan plisiasoun apomakrynontai
MovingPathAnimation* AI::createSmallGreenGreyBirdAnimation() {
	std::list<PathEntry> paths;
	//todo appropriately
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.20, 180, 360, littleBirdSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(-100, -100, littleBirdSpeed));
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.17, 180, 720, littleBirdSpeed));
	return new MovingPathAnimation(paths, lastUsedID++);
}

MovingPathAnimation* AI::createSmallBlueGreyBirdAnimation() {
	std::list<PathEntry> paths;
	//todo appropriately
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.20, 180, 360, littleBirdSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(-100, -100, littleBirdSpeed));
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.17, 180, 720, littleBirdSpeed));
	return new MovingPathAnimation(paths, lastUsedID++);
}

MovingPathAnimation* AI::createSmallYellowGreyBirdAnimation() {
	std::list<PathEntry> paths;
	//todo appropriately
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.20, 180, 360, littleBirdSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(-100, -100, littleBirdSpeed));
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.17, 180, 720, littleBirdSpeed));
	return new MovingPathAnimation(paths, lastUsedID++);
}