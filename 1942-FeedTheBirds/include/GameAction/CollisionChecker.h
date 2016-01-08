#ifndef _COLLISIONCHECKER_H
#define _COLLISIONCHECKER_H

#include <stdio.h>
#include <allegro5/allegro.h>
#include <list>
#include "..\Sprites\Sprite.h"

// TODO: fix values!
#define UP_BORDER 512
#define DOWN_BORDER 0
#define LEFT_BORDER 0 
#define RIGHT_BORDER 0

typedef std::pair<Sprite*, Sprite*> Pair;

class CollisionChecker {
	static CollisionChecker *collisionChecker;

	std::list<Pair> pairs;

	struct checkFunctor : public std::unary_function<Pair, void> {
		void operator()(const Pair& p) const { 
			p.first->collisionCheck(p.second); 
		}
	};

protected:
	CollisionChecker(void);

public:
	static void initialize(void);
	static CollisionChecker *getInstance(void);
	bool collidesWithBorders(Sprite *s);
	void registerCollisionsWithPows(Sprite* s1);
	void registerCollisions(Sprite* s1, Sprite* s2);
	void cancel(Sprite* s1, Sprite* s2);
	void check(void) const;
};

#endif