#include "..\..\include\GameAction\CollisionChecker.h"
#include <algorithm>

using namespace std;
CollisionChecker *CollisionChecker::collisionChecker;

CollisionChecker::CollisionChecker(void) {
}

CollisionChecker::~CollisionChecker(void) {
	CollisionChecker::pairs.clear();
	assert(pairs.size() == 0);
}

void CollisionChecker::singletonCreate(void) {
	if (collisionChecker == NULL)
		collisionChecker = new CollisionChecker();
}

void CollisionChecker::singletonDestroy(void) {
	if (collisionChecker)
		delete collisionChecker;
}

void CollisionChecker::clear(void) { 
	CollisionChecker::pairs.clear();
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

void CollisionChecker::cancel(Sprite* s1, Sprite* s2) {
	assert(s1); assert(s2);
	unsigned int oldSize;
	oldSize = pairs.size();	

	std::list<Pair>::iterator it = pairs.begin();
	for (unsigned int i = 1; i <= oldSize; i++) {

		std::advance(it, i);

		if (find(*it, s1, s2)) {
			pairs.erase(it);
			assert(pairs.size() == oldSize - 1);
			break;
		}
	}
}

bool CollisionChecker::find(Pair pair, Sprite* s1, Sprite* s2) {
	if ((pair.first == s1 && pair.second == s2) ||
		(pair.first == s2 && pair.second == s1)) {
		return true;
	}
	return false;
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