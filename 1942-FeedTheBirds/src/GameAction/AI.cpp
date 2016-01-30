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

std::list<PathEntry>* AI::createSmoothDiagonalPath(int dx, int dy) {//close enough
	std::list<PathEntry> *paths = new std::list<PathEntry>;
	int sumx, sumy, absx, absy, ratio,  diff;
	sumx = 0;
	sumy = 0;
	absx = (dx < 0 ? -dx : dx);
	absy = (dy < 0 ? -dy : dy);
	if (absx > absy) {
		ratio = (int)round((double)(((double)absx) / ((double)absy)));
		for (;sumx<absx;) {
			if ( absy && sumy<absy &&
				!((sumx - sumy) % ratio)
				){
				diff = (int)round(((double)1 / (double)ratio*sumx - sumy));
				paths->push_back(PathEntry((dx < 0 ? -2: 2), (int)(dy < 0 ? -diff: diff), false, false, 0, 12));
				//cout << "1Just added dx=" << paths->back().dx << " dy=" << paths->back().dy << endl;
				sumy+= diff;
				sumx++;
			}
			else {
				paths->push_back(PathEntry((dx < 0 ? -1 : 1), 0, false, false, 0, 12));
				//cout << "2Just added dx=" << paths->back().dx << " dy=" << paths->back().dy << endl;
			}
			sumx++;
		}
		if (sumy < absy) {
			for (;sumy < absy;sumy++) {
				paths->push_back(PathEntry(0, (dy < 0 ? -1 : 1), false, false, 0, 12));
				//cout << "3Just added dx=" << paths->back().dx << " dy=" << paths->back().dy << endl;
			}
		}
	}
	else {
		ratio = (int)round((double)(((double)absy) / ((double)absx)));
		for (;sumy<absy;) {
			if (absx && sumx<absx &&
				!((sumy - sumx) % ratio)
				) {
				diff = (int)round(((double)1 / (double)ratio*sumy - sumx));
				paths->push_back(PathEntry((dx < 0 ? - diff: diff), (dy < 0 ? -2 : 2), false, false, 0, 12));
				//cout << "4Just added dx=" << paths->back().dx << " dy=" << paths->back().dy << endl;
				sumx+= diff;
				sumy++;
			}
			else {
				paths->push_back(PathEntry(0, (dy < 0 ? -1 : 1), false, false, 0, 12));
				//cout << "5Just added dx=" << paths->back().dx << " dy=" << paths->back().dy << endl;
			}
			sumy++;
		}
		if (sumx < absx) {
			for (;sumx < absx;sumx++) {
				paths->push_back(PathEntry((dx < 0 ? -1 : 1), 0, false, false, 0, 12));
				//cout << "6Just added dx=" << paths->back().dx << " dy=" << paths->back().dy << endl;
			}
		}
	}
	return paths;
}

std::list<PathEntry>* AI::createCircularPath(int radius, int startAngle, int endAngle) {
	std::list<PathEntry> *paths= new std::list<PathEntry>;
	int lastx, lasty, i;
	i = startAngle-1;
	lastx = XforCircle(radius);
	lasty = YforCircle(radius);
	paths->push_back(PathEntry(0, 0, false, false, 0, 0));
	for (int i = startAngle; i < endAngle; i += 1) {
		paths->push_back(
			PathEntry(
				XforCircle(radius) - lastx,
				-(YforCircle(radius) - lasty),
				false, false, 0, 25));
		lastx = XforCircle(radius);
		lasty = YforCircle(radius);
		//cout << "Just added dx=" << paths->back().dx << " dy=" << paths->back().dy << endl;
	}
	paths->push_back(PathEntry(0, 0, false, false, 0, 0));
	return paths;
}