#include "..\..\include\Sprites\Sprite.h"

Sprite::Sprite(Dim _x, Dim _y, AnimationFilm* film) :
	x(_x), y(_y), 
	currFilm(film), 
	isVisible(true), 
	flip_h(false), flip_v(false) {
	frameNo = currFilm->getTotalFrames();
	setFrame(0);
}

Sprite::~Sprite() {
	currFilm = nullptr;
	frameNo = 0;
	isVisible = false;
}

void Sprite::setFrame(byte i) {
	if (currFilm->getTotalFrames() > 1) {
		if (i != frameNo) {
			//assert(i < currFilm->GetTotalFrames());
			if (i >= currFilm->getTotalFrames()) i = 0;
			frameBox = currFilm->getFrameBox(frameNo = i);
		}
	}
}

byte Sprite::getFrame(void) const { 
	return frameNo;
}

Rect Sprite::getRect(void) const {
	Rect bbox = currFilm->getFrameBox(frameNo);
	assert(bbox.w!=0 && bbox.h!=0 && "bbox empty");
	return Rect(x, y, bbox.w, bbox.h);
	//return Rect(x, y, SCALE*bbox.w, SCALE*bbox.h);
}

void Sprite::setAnimationFilm(AnimationFilm *animF) {
	currFilm = animF;
	frameNo = animF->getTotalFrames();
	setFrame(0);
};

void Sprite::setVisibility(bool v) {
	isVisible = v;
}

bool Sprite::isSpriteVisible(void) const {
	return isVisible;
}

Rect Sprite::getFrameBox(void) {
	return currFilm->getFrameBox(frameNo); 
}

void Sprite::setX(int _x) {
	x = _x; 
}

int Sprite::getX(void) { 
	return x; 
}

void Sprite::setY(int _y) { 
	y = _y; 
}

int Sprite::getY(void) { 
	return y; 
}

void Sprite::setFlipH(bool _flip_h) { 
	flip_h = _flip_h; 
}

bool Sprite::getFlipH(void) { 
	return flip_h; 
}

void Sprite::setFlipV(bool _flip_v) { 
	flip_v = _flip_v; 
}

bool Sprite::getFlipV(void) { 
	return flip_v; 
}

void Sprite::enableMovement(void) { 
	canMove = true; 
}

void Sprite::disableMovement(void) { 
	canMove = false; 
}

bool Sprite::collisionCheck(Sprite* s) {
	if (s->isSpriteVisible()) {
		int x1, y1, x2, y2, x3, y3, x4, y4;
		Rect b1, b2;
		b1 = s->getRect();
		x1 = b1.x;
		y1 = b1.y;
		x2 = x1 + b1.w;
		y2 = y1 + b1.h;
		b2 = this->getRect();
		x3 = b2.x;
		y3 = b2.y;
		x4 = x3 + b2.w;
		y4 = y3 + b2.h;
		//printf("[(%d,%d),(%d,%d)], [(%d,%d),(%d,%d)]\n", x1, y1, x2, y2, x3, y3, x4, y4);
		if ((!(x2 < x3) && !(x1 > x4)) && (!(y2 < y3) && !(y1 > y4))) {
			collisionAction(s);
			return true;
		}
	}
	return false;
}

// TODO: check if correct!
// image arg is not used!!!
void Sprite::display(Rect image) {
	currFilm->displayFrame(Point(x, y), frameNo, flip_h, flip_v);
	//al_draw_bitmap_region(currFilm->GetBitmap(), frameBox.x, frameBox.y, frameBox.w, frameBox.h, da.x, da.y, 0);
}

void Sprite::move(int x, int y) {
		this->x += x;
		this->y += y;
}
