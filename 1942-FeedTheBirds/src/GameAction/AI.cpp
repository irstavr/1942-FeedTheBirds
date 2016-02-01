#include "..\..\include\GameAction\AI.h"

AI::AI(GameLogic *_gameLogic, FrameRangeAnimator* _flyAnimator, FrameRangeAnimation *_flyAnimation):
			gameLogic(_gameLogic),
			flyAnimator(_flyAnimator),
			flyAnimation(_flyAnimation) {
	lastUsedID = BASE_ID;
	birds = gameLogic->birds;
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

	/* initialize random seed: */
	srand(time(NULL));
}

AI::~AI() {
}

void AI::eventAtX(int x)
{
	handleLittleBirds();
	handleMediumBirds();
	handleBoss();

	switch (x) {
	case 20:
		// action point for small birds
		this->addSmallBird(SCREEN_WINDOW_WIDTH*0.75, 
							SCREEN_WINDOW_HEIGHT+10, 
							"smallGreenBird", 
							smallGreenBirdAnimation);
		this->addSmallBird(SCREEN_WINDOW_WIDTH*0.75+50, 
							SCREEN_WINDOW_HEIGHT+60, 
							"smallYellowBird", 
							smallYellowBirdAnimation);
		this->addSmallBird(SCREEN_WINDOW_WIDTH*0.75+100, 
							SCREEN_WINDOW_HEIGHT+200, 
							"smallBlueBird", 
							smallBlueBirdAnimation);
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
		addMediumBirds();
		break;
	case 500:
		// action point for boss
		break;
	case 3480:	// TODO: change to terrain length minus something : P
		gameLogic->superAce->startLanding();
		break;
	default:
		break;
	}
}

//------------------------ Boss Birds --------------------------------------------------

void AI::handleBoss() {
	
}

MovingPathAnimation* AI::createBigBirdAnimation() {
	std::list<PathEntry> paths;
	return new MovingPathAnimation(paths, 0);
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

	// random num of birds each time (max 10)
	int birdsNum = rand() % 10;	// TODO: to be used inside ifs

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
		this->addMediumBird(SCREEN_WINDOW_WIDTH-300,
							SCREEN_WINDOW_HEIGHT/2,
							"mediumBrownBird",
							mediumColoredBirdLives,
							mediumColoredBirdSpeed,
							mediumBrownBirdAnimation);
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
			if ((*it)->hasFinished()) {
				bird->scare();
			}
			else if (
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
	}
}

void AI::addMediumBird(int x, int y, char* filmId, BirdLives lives, BirdSpeed speed, MovingPathAnimation* visVitalis) {

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
}

// create a Brown Medium Bird
//apo to panw meros ths othonis kanoun ena kuklo k sunexizoun na mas vroun
MovingPathAnimation* AI::createMediumBrownBirdAnimation() {
	std::list<PathEntry> paths;
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.10, 180, 360, mediumColoredBirdSpeed));
	//paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.10, 360, 720, mediumColoredBirdSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(SCREEN_WINDOW_WIDTH, 0, mediumColoredBirdSpeed));
	return new MovingPathAnimation(paths, 0);
}

// apo to katw meros ki anevainoun
MovingPathAnimation* AI::createMediumGreenBirdAnimation() {
	std::list<PathEntry> paths;
	//todo appropriately
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.20, 180, 360, mediumColoredBirdSpeed));
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.10, 180, 720, mediumColoredBirdSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(-100, -100, mediumColoredBirdSpeed));
	return new MovingPathAnimation(paths, 0);
}

// se smhnos (ki ap tis 2 pleures) 
MovingPathAnimation* AI::createMediumYellowBirdAnimation() {
	std::list<PathEntry> paths;
	//todo appropriately
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.20, 180, 360, mediumColoredBirdSpeed));
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.10, 180, 720, mediumColoredBirdSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(-100, -100, mediumColoredBirdSpeed));
	return new MovingPathAnimation(paths, 0);
}

// idia kinisi apla me megalutero speed
MovingPathAnimation* AI::createMediumGreyBirdAnimation() {
	std::list<PathEntry> paths;
	//todo appropriately
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.20, 180, 360, mediumGreyBirdSpeed));
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.10, 180, 720, mediumGreyBirdSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(-100, -100, mediumGreyBirdSpeed));
	return new MovingPathAnimation(paths, 0);
}

//------------------------ Small Birds --------------------------------------------------

void AI::addSmallBird(int x, int y, char* filmId, MovingPathAnimation* visVitalis) {
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
			else if (
				(bird->getY() >= gameLogic->superAce->getY()*0.9) &&
				(bird->getY() <= gameLogic->superAce->getY()*1.1) &&
				!(rand() % 31)
				)//Bird is within 20% of superAce's y
			{
				BirdDropping* dropping = bird->shoot();
				bird->decrFire();
				CollisionChecker::getInstance()->registerCollisions(gameLogic->superAce, dropping);
			}
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
	return new MovingPathAnimation(paths, 0);
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
	return new MovingPathAnimation(paths, 0);
}

//bonus bird
MovingPathAnimation* AI::createSmallRedBirdAnimation() {
	std::list<PathEntry> paths;
	//todo appropriately
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.20, 180, 360, littleBirdSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(-100, -100, littleBirdSpeed));
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.17, 180, 720, littleBirdSpeed));
	return new MovingPathAnimation(paths, 0);
}

//megalyteres kampyles, apeutheias epitheseis
MovingPathAnimation* AI::createSmallYellowBirdAnimation() {
	std::list<PathEntry> paths;
	//todo appropriately
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.30, 180, 360, littleBirdSpeed));
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.20, 180, 720, littleBirdSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(-100, -100, littleBirdSpeed));
	return new MovingPathAnimation(paths, 0);
}

//erxontai katheta (apo ta deksia) kai sto telos plisiazoun ton SuperAce
//erxontai diagwnia pros ton superAce kai otan plisiasoun apomakrynontai
MovingPathAnimation* AI::createSmallGreenGreyBirdAnimation() {
	std::list<PathEntry> paths;
	//todo appropriately
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.20, 180, 360, littleBirdSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(-100, -100, littleBirdSpeed));
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.17, 180, 720, littleBirdSpeed));
	return new MovingPathAnimation(paths, 0);
}

MovingPathAnimation* AI::createSmallBlueGreyBirdAnimation() {
	std::list<PathEntry> paths;
	//todo appropriately
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.20, 180, 360, littleBirdSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(-100, -100, littleBirdSpeed));
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.17, 180, 720, littleBirdSpeed));
	return new MovingPathAnimation(paths, 0);
}

MovingPathAnimation* AI::createSmallYellowGreyBirdAnimation() {
	std::list<PathEntry> paths;
	//todo appropriately
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.20, 180, 360, littleBirdSpeed));
	paths.splice(paths.end(), *createSmoothDiagonalPath(-100, -100, littleBirdSpeed));
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.17, 180, 720, littleBirdSpeed));
	return new MovingPathAnimation(paths, 0);
}