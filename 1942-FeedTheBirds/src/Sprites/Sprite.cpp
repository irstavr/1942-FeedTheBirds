#include "..\..\include\Sprites\Sprite.h"

Sprite::Sprite(Dim _x, Dim _y, AnimationFilm* film) :
	x(_x), y(_y), currFilm(film), isVisible(true), flip_h(false), flip_v(false)
{
	frameNo = currFilm->getTotalFrames();
	setFrame(0);
}

void Sprite::setFrame(byte i) {
	//TODO
}

byte Sprite::getFrame(void) const { return frameNo; }

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

void Sprite::setVisibility(bool v) { isVisible = v; }

bool Sprite::isSpriteVisible(void) const { return isVisible; }
