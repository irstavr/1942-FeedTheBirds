#include "..\..\include\Sprites\Sprite.h"

Sprite::Sprite(Dim _x, Dim _y, AnimationFilm* film) :
	x(_x), y(_y), 
	currFilm(film), 
	isVisible(true), 
	flip_h(false), flip_v(false) {
	frameNo = currFilm->getTotalFrames();
	setFrame(0);
}

void Sprite::setFrame(byte i) {
	//TODO
}

byte Sprite::getFrame(void) const { 
	return frameNo;
}

Rect Sprite::getRect(void) const {
	Rect bbox = currFilm->getFrameBox(frameNo);
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
	// TODO 
	return true;
}

// TODO: check if correct!
// image arg is not used!!!
void Sprite::display(ALLEGRO_BITMAP* image) {
	currFilm->displayFrame(Point(x, y), frameNo, flip_h, flip_v);
	//al_draw_bitmap_region(currFilm->GetBitmap(), frameBox.x, frameBox.y, frameBox.w, frameBox.h, da.x, da.y, 0);
}

void Sprite::move(int x, int y) {
	this->x += x;
	this->y += y;
}
