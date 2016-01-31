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
	case 100:
		this->addSmallBird(SCREEN_WINDOW_WIDTH*0.75, SCREEN_WINDOW_HEIGHT+10, "smallGreenBird", smallGreenBirdAnimation);
		this->addSmallBird(SCREEN_WINDOW_WIDTH*0.75+50, SCREEN_WINDOW_HEIGHT+60, "smallYellowBird", smallYellowBirdAnimation);
		this->addSmallBird(SCREEN_WINDOW_WIDTH*0.75+100, SCREEN_WINDOW_HEIGHT+200, "smallRedBird", smallRedBirdAnimation);
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
	this->smallBirds->back()->start(
		gameLogic->createBird(x, y, 
							littleBird,
							littleBirdLives,
							littleBirdSpeed, // TODO: TO BE USED on AI!
							filmId,
							flyAnimation->clone(lastUsedID++),
							flyAnimator->clone()),
		visVitalis->clone(lastUsedID++), getCurrTime());
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
				CollisionChecker::getInstance()->registerCollisions(gameLogic->superAce, dropping);
			}
		}
	}
}

void AI::handleMediumBirds() {

}

void AI::handleBoss() {

}

MovingPathAnimation* AI::createbigBirdAnimation() {
	std::list<PathEntry> paths;
	return new MovingPathAnimation(paths, 0);
}

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

MovingPathAnimation* AI::createSmallGreenBirdAnimation() {
	std::list<PathEntry> paths;
	//todo appropriately
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.20, 180, 360));
	paths.splice(paths.end(), *createSmoothDiagonalPath(-100, -100));
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.17, 180, 720));
	return new MovingPathAnimation(paths, 0);
}

MovingPathAnimation* AI::createSmallBlueBirdAnimation() {
	std::list<PathEntry> paths;
	//todo appropriately
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.20, 180, 360));
	paths.splice(paths.end(), *createSmoothDiagonalPath(-100, -100));
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.17, 180, 720));
	return new MovingPathAnimation(paths, 0);
}

MovingPathAnimation* AI::createSmallRedBirdAnimation() {
	std::list<PathEntry> paths;
	//todo appropriately
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.20, 180, 360));
	paths.splice(paths.end(), *createSmoothDiagonalPath(-100, -100));
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.17, 180, 720));
	return new MovingPathAnimation(paths, 0);
}

MovingPathAnimation* AI::createSmallYellowBirdAnimation() {
	std::list<PathEntry> paths;
	//todo appropriately
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.20, 180, 360));
	paths.splice(paths.end(), *createSmoothDiagonalPath(-100, -100));
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.17, 180, 720));
	return new MovingPathAnimation(paths, 0);
}
