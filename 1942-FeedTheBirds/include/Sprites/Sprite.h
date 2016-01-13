#ifndef SP_H
#define SP_H

#include <string>
#include <utility>

#include "..\Animation\AnimationFilm.h"
#include "..\Utilities\Utilities.h"
using namespace std;


class Sprite {
	AnimationFilm* currFilm;
	Dim x, y;
	byte frameNo;
	Rect frameBox;
	bool flip_h, flip_v;
	bool isVisible;

	bool canMove;

public:
	Sprite(Dim _x, Dim _y, AnimationFilm* film);

	void setFrame(byte i);
	byte getFrame(void) const;
	Rect getFrameBox(void);
	Rect getRect(void) const;
	void setAnimationFilm(AnimationFilm *);
	
	virtual void resetToDefaultFilm(void) {};

	void setX(int _x);
	int  getX(void);
	void setY(int _y);
	int  getY(void);
	void setFlipH(bool _flip_h);
	bool getFlipH(void);
	void setFlipV(bool _flip_v);
	bool getFlipV(void);

	void setVisibility(bool v);
	bool isSpriteVisible(void) const;
	bool collisionCheck(Sprite* s);
	
	virtual void collisionAction(Sprite* s) {};
	
	void enableMovement(void);
	void disableMovement(void);

	virtual void move(int x, int y);
	void display(Rect image);
};



#endif