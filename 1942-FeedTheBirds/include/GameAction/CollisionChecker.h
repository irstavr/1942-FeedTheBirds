#ifndef _COLLISIONCHECKER_H
#define _COLLISIONCHECKER_H

#include "..\Sprites\Sprite.h"

#include <allegro5/allegro.h>
#include <iostream>
#include <stdio.h>
#include <list>
#include <assert.h>

#define UP_BORDER 0
#define DOWN_BORDER 669
#define LEFT_BORDER 0
#define RIGHT_BORDER 1300

typedef std::pair<Sprite*, Sprite*> Pair;

class CollisionChecker {

private:
	static CollisionChecker *collisionChecker;

	// All the possible collision pairs:
	// super ace - birds -> DIE SUPER ACE - GAMEOVER/LOSE LIFE
	// super ace - birdshits -> DIE SUPER ACE
	// super ace - pows -> activate LEVELUP SUPERACE
	// birds - fishes -> BIRD LOSES LIFE
	// birds - borders -> KILL BIRD SPRITE
	// fishes - borders -> KILL FISH SPRITE
	// birdshits - borders -> KILL BIRDSHIT SPRITE
	std::list<Pair> pairs;

	struct checkFunctor : public std::unary_function<Pair, void> {
		void operator()(const Pair& p) const { 
			p.first->collisionCheck(p.second); 
		}
	};

	bool find(Pair pair, Sprite* s1, Sprite* s2);

public:
	CollisionChecker(void);
	~CollisionChecker(void);

	static void singletonCreate(void);
	static void singletonDestroy(void);
	static CollisionChecker *getInstance(void);

	bool collidesWithBorders(Sprite *s);
	void registerCollisions(Sprite* s1, Sprite* s2);
	void cancel(Sprite* s1, Sprite* s2);
	void check(void) const;
	void clear();
};
#endif