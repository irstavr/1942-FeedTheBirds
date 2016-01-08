#ifndef SP_H
#define SP_H

#include <string>
#include <utility>

#include "..\Animation\AnimationFilm.h"

using namespace std;

typedef int Dim;
typedef unsigned char byte;
typedef pair<float, float> COORDS;

class Sprite {
	byte frameNo;
	Rect frameBox;
	Dim x, y;
	bool flip_h, flip_v;
	bool isVisible;
	AnimationFilm* currFilm;

	bool canMove;

public:
	Sprite(Dim _x, Dim _y, AnimationFilm* film);

	void setFrame(byte i);
	byte getFrame(void) const;
	Rect getFrameBox(void) { return currFilm->getFrameBox(frameNo); };
	Rect getRect(void) const;
	void setAnimationFilm(AnimationFilm *);
	virtual void resetToDefaultFilm(void) {};

	void setX(int _x) { x = _x; };
	int getX(void) { return x; };
	void setY(int _y) { y = _y; };
	int getY(void) { return y; };
	void setFlipH(bool _flip_h) { flip_h = _flip_h; };
	bool getFlipH(void) { return flip_h; };
	void setFlipV(bool _flip_v) { flip_v = _flip_v; };
	bool getFlipV(void) { return flip_v; };

	void setVisibility(bool v);
	bool isSpriteVisible(void) const;
	bool collisionCheck(Sprite* s);
	virtual void collisionAction(Sprite* s) {};
	void display(const Rect& da);
	//virtual void move(int x, int y);

	void enableMovement(void) { canMove = true; };
	void disableMovement(void) { canMove = false; };
};



#endif