#include "..\..\include\GameAction\AI.h"

AI::AI(GameLogic *_gameLogic, FrameRangeAnimator* _flyAnimator, FrameRangeAnimation *_flyAnimation):
			gameLogic(_gameLogic),
			flyAnimator(_flyAnimator),
			flyAnimation(_flyAnimation) {
	lastUsedID = BASE_ID;
	birds = gameLogic->birds;
	smallBirds  = new std::vector<MovingPathAnimator*>;
	mediumBirds = new std::vector<Bird*>;
	largeBirds  = new std::vector<Bird*>;
	bonusBirds  = new std::vector<Bird*>;

	birdPathAnimator = new MovingPathAnimator();

	smallGreenBirdAnimation = this->createSmallGreenBirdAnimation();
	smallBlueBirdAnimation = this->createSmallBlueBirdAnimation();
	smallRedBirdAnimation = this->createSmallRedBirdAnimation();
	smallYellowBirdAnimation = this->createSmallYellowBirdAnimation();
}

AI::~AI() {
}

void AI::eventAtX(int x)
{
	handleLittleBirds();
	switch (x) {
	case 20:
		this->addSmallBird(SCREEN_WINDOW_WIDTH*0.75, SCREEN_WINDOW_HEIGHT+10, "smallGreenBird", smallGreenBirdAnimation);
		this->addSmallBird(SCREEN_WINDOW_WIDTH*0.75+50, SCREEN_WINDOW_HEIGHT+60, "smallYellowBird", smallYellowBirdAnimation);
		this->addSmallBird(SCREEN_WINDOW_WIDTH*0.75+100, SCREEN_WINDOW_HEIGHT+200, "smallBlueBird", smallBlueBirdAnimation);
		break;
	case 1000:	// terrain length minus something : P
		gameLogic->superAce->startLanding();
		break;
	default:
		break;
	}
}

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
	for (auto it = this->smallBirds->begin(); it != this->smallBirds->end();it++)
	{
		bird = (Bird*)(*it)->getSprite();
		if (!bird->isDead()) {
			if ((*it)->hasFinished()) {
				bird->scare();
			}
			else if(
				(bird->getY() >= gameLogic->superAce->getY()*0.9) &&
				(bird->getY() <= gameLogic->superAce->getY()*1.1) &&
				!(rand()%31)
				)//Bird is within 20% of superAce's y
			{
				BirdDropping* dropping = bird->shoot();
				bird->decrFire();
				CollisionChecker::getInstance()->registerCollisions(gameLogic->superAce, dropping);
			}
		}
	}
}

void AI::handleMediumBirds() {

}

void AI::handleBoss() {

}

MovingPathAnimation* AI::createBigBirdAnimation() {
	std::list<PathEntry> paths;
	return new MovingPathAnimation(paths, 0);
}

//------------------------ Medium Birds -------------------------------------------------

MovingPathAnimation* AI::createMediumBrownBirdAnimation() {
	std::list<PathEntry> paths;
	return new MovingPathAnimation(paths, 0);
}

MovingPathAnimation* AI::createMediumGreenBirdAnimation() {
	std::list<PathEntry> paths;
	return new MovingPathAnimation(paths, 0);
}

MovingPathAnimation* AI::createMediumYellowBirdAnimation() {
	std::list<PathEntry> paths;
	return new MovingPathAnimation(paths, 0);
}

//------------------------ Small Birds --------------------------------------------------

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
