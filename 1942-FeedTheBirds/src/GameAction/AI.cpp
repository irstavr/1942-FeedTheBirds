#include "..\..\include\GameAction\AI.h"

AI::AI(GameLogic *_gameLogic, FrameRangeAnimator* _flyAnimator, FrameRangeAnimation *_flyAnimation):
			gameLogic(_gameLogic),
			flyAnimator(_flyAnimator),
			flyAnimation(_flyAnimation) {
	lastUsedID = BASE_ID;
	birds = gameLogic->birds;
	smallBirds  = new std::vector<Bird*>;
	mediumBirds = new std::vector<Bird*>;
	largeBirds  = new std::vector<Bird*>;
	bonusBirds  = new std::vector<Bird*>;
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
		this->addLittleBird(1000, 400);
		this->addLittleBird(1200, 400);
		this->addLittleBird(1400, 400);
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
	this->smallBirds->push_back(gameLogic->createBird(
								x, y, 
								2, //bird lives
								(char*)sstr.str().c_str(),
								flyAnimation->clone(lastUsedID++),
								flyAnimator->clone()));
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
				(*it)->flyAnimation->setDy(-((*it)->getY() - gameLogic->superAce->getY()));
				(*it)->flyAnimation->setDx(-((*it)->getX() - (gameLogic->superAce->getX() + 200)));
			}

		}
}

void AI::handleMediumBirds() {

}

void AI::handleBoss() {

}