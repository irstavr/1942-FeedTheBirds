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
	smallGreenBirdAnimation = this->createSmallGreenBirdAnimation();
	smallGreenBirdAnimator = new MovingPathAnimator();
}

AI::~AI() {
}

void AI::eventAtX(int x)
{
	handleLittleBirds();
	switch (x) {
	case 10:
		//gameLogic->superAce->startTakeOff();
		break;
	case 100:
		this->addLittleBird(SCREEN_WINDOW_WIDTH*0.75, SCREEN_WINDOW_HEIGHT-10);
		this->addLittleBird(SCREEN_WINDOW_WIDTH*0.75+50, SCREEN_WINDOW_HEIGHT-10);
		this->addLittleBird(SCREEN_WINDOW_WIDTH*0.75+100, SCREEN_WINDOW_HEIGHT-10);
		break;
	default:
		break;
	}
}

void AI::addBonusBird(int x, int y) {
	this->bonusBirds->push_back(gameLogic->
									createBird(x, y,
												1,	//bird lives
												"bonusBird",
												flyAnimation->clone(lastUsedID++),
												flyAnimator->clone()));
}

void AI::addLittleBird(int x, int y) {
	std::ostringstream sstr;
	sstr << "smallBird" << ((x + y) % 3)+1;
	
	this->smallBirds->push_back(smallGreenBirdAnimator->clone());
	this->smallBirds->back()->setHandleFrames(false);
	AnimatorHolder::markAsRunning(this->smallBirds->back());
	this->smallBirds->back()->start(
		gameLogic->createBird(
			x, y, 1,
			(char*)sstr.str().c_str(),
			flyAnimation->clone(lastUsedID++),
			flyAnimator->clone()),
		smallGreenBirdAnimation->clone(lastUsedID++), getCurrTime());

	

}

void AI::handleLittleBirds()
{
		for (std::vector<Bird*>::iterator it = this->birds->begin(); it != this->birds->end();it++)
		{
			if (!(*it)->isDead()) {
				if(
					((*it)->getY() >= gameLogic->superAce->getY()*0.9) && 
					((*it)->getY() <= gameLogic->superAce->getY()*1.1) &&
					!(rand()%131)
					)//Bird is within 20% of superAce's y
				{
					BirdDropping* dropping = (*it)->shoot();
					CollisionChecker::getInstance()->registerCollisions(gameLogic->superAce, dropping);
				}
				if (YY<=0) {
					//(*it)->flyAnimation->setDy(PIXELS_PER_SECOND / LPS);
				}
				else {
					//(*it)->flyAnimation->setDy(-PIXELS_PER_SECOND / LPS);
				}

				if (XX <=0) {
					//cout << "Setting dx= " << (*it)->flyAnimation->getDx() << endl;
					//(*it)->flyAnimation->setDx(PIXELS_PER_SECOND / LPS);
				}
				else {
					//cout << "dx= "<< (*it)->flyAnimation->getDx() << endl;
					//(*it)->flyAnimation->setDx(-PIXELS_PER_SECOND / LPS);
				}


				//(*it)->flyAnimation->setDx(-((*it)->getX() - (gameLogic->superAce->getX() + 200)));
			}

		}
}

void AI::handleMediumBirds() {

}

void AI::handleBoss() {

}

MovingPathAnimation* AI::createSmallGreenBirdAnimation() {
	std::list<PathEntry> paths;
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.3, 180, 360));
	return new MovingPathAnimation(paths, 0);
}


std::list<PathEntry>* AI::createCircularPath(int radius, int startAngle, int endAngle) {
	std::list<PathEntry> *paths= new std::list<PathEntry>;
	int lastx, lasty, i;
	i = startAngle-1;
	lastx = XforCircle(radius);
	lasty = YforCircle(radius);
	paths->push_back(PathEntry(0, 0, false, false, 0, 0));
	for (int i = startAngle; i < endAngle; i += 2) {
		paths->push_back(
			PathEntry(
				XforCircle(radius) - lastx,
				-(YforCircle(radius) - lasty),
				false, false, 0, 50));
		lastx = XforCircle(radius);
		lasty = YforCircle(radius);
		//cout << "Just added dx=" << paths->back().dx << " dy=" << paths->back().dy << endl;
	}
	paths->push_back(PathEntry(0, 0, false, false, 0, 0));
	return paths;
}


