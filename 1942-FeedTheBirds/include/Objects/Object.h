#ifndef _OBJECT_H
#define _OBJECT_H

#include <vector>
#include <memory>
#include "..\Sprites\Sprite.h"

class Object {
	Object(const std::string& name);
	virtual ~Object();
};
#if 0
//Our Player
struct SpaceShip
{
	int ID;
	int x;
	int y;
	int lives;
	int speed;
	int boundx;
	int boundy;
	int score;
};

struct Bullet
{
	int ID;
	int x;
	int y;
	bool live;
	int speed;
};
 
struct Comet
{
	int ID;
	int x;
	int y;
	bool live;
	int speed;
	int boundx;
	int boundy;
};
#endif

#endif