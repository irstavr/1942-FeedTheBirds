#include "..\..\include\GameAction\CollisionChecker.h"
#include <algorithm>
//#include "PowsHolder.h"

using namespace std;

CollisionChecker *CollisionChecker::collisionChecker;

CollisionChecker::CollisionChecker(void) {
}

CollisionChecker::~CollisionChecker(void) {
}

void CollisionChecker::cleanUp() {
	delete collisionChecker;
}

void CollisionChecker::initialize(void) {
	if (collisionChecker == NULL)
		collisionChecker = new CollisionChecker();
}

CollisionChecker *CollisionChecker::getInstance(void) {
	return collisionChecker;
}

void CollisionChecker::registerCollisions (Sprite* s1, Sprite* s2) {
	Pair p;
	p.first = s1;
	p.second = s2;
	pairs.push_back(p);
}

void CollisionChecker::registerCollisionsWithPows(Sprite* superAce) {
	/*
	Pair p;
	p.second = superAce;
	std::list<Pows *>powsList = PowsHolder::getHeartList();
	std::list<Pows *>::iterator i = powsList.begin();
	advance(i, PowsHolder::inForCheck);

	while (i != powsList.end()) {
		p.first = (*i);
		pairs.push_back(p);
		++i;
		++PowsHolder::inForCheck;
	}
	*/
}

void CollisionChecker::cancel(Sprite* s1, Sprite* s2) {
}

void CollisionChecker::check(void) const {
	std::for_each(pairs.begin(), pairs.end(), checkFunctor());
}

bool CollisionChecker::collidesWithBorders(Sprite *s) {
	if (s->getX() - 10 < LEFT_BORDER) return true;
	if (s->getX() + 10 > RIGHT_BORDER) return true;

	if (s->getY() + 10 > UP_BORDER) return true;
	if (s->getY() + 10 > DOWN_BORDER) return true;
	return false;
}