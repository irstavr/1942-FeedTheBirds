#ifndef _OBJECT_H
#define _OBJECT_H

#include <vector>
#include <memory>

class Rect {
public:
	int x, y, w, h;
	Rect(int _x, int _y, int _w, int _h);
	Rect();

	bool Rect::operator==(const Rect &other) const;
};

class Point {
public:
	Point(int _x, int _y);
	Point();

	int x, y;
	void setPoint(int _x, int _y);
};

#endif