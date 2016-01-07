#ifndef _OBJECT_H
#define _OBJECT_H

#include <vector>
#include <memory>

class Rect {
public:
	int x, y, w, h;
	Rect(int _x, int _y, int _w, int _h) : x(_x), y(_y), w(_w), h(_h) {};
	Rect() :x(0), y(0), w(0), h(0) {};

	bool Rect::operator==(const Rect &other) const {
		if ((this->x == other.x) && (this->y == other.y) && (this->w == other.w) && (this->h == other.h))
			return true;

		return false;
	}
};

class Point {
public:	
	int x, y;
	void setPoint(int _x, int _y) { x = _x; y = _y; };
	Point(int _x, int _y) : x(_x), y(_y) {};
	Point() : x(0), y(0) {};
};

#endif