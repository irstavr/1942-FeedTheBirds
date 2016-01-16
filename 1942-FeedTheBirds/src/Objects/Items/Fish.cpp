#include "..\..\..\include\Objects\Items\Fish.h"

/*
Fish::Fish(int d, int t) : direction(d) {
	//set speed according to type
	switch (t) {
		case 1:
			speedX = 1;
			speedY = d == -1 ? 700 : 350;
			break;
		case 2:
			speedX = 150;
			speedY = 350;
			break;
		case 3:
			speedX = -150;
			speedY = 350;
			break;
	}
}
*/

// TODO: if bonuses change bullets
// add another field for advancing speed
Fish::Fish(Dim _x, Dim _y, AnimationFilm* film,
	FrameRangeAnimation *_flyAnimation, FrameRangeAnimator *_flyAnimator,
	FlashingAnimation *_flashAnimation, FlashingAnimator *_flashingAnimator) :
	Sprite(_x, _y, film),
	flyAnimation(_flyAnimation),
	flyAnimator(_flyAnimator),
	flashAnimation(_flashAnimation),
	flashAnimator(_flashingAnimator) {
	isInvisible = false;
	isMetWithBird = false;
}

bool Fish::inRange(float x, float y, float num) {
	return ((num >= x) && (num <= y));
}

void Fish::move(float dt, float &x, float&y) {
	y += direction * speedY * dt;
	x += direction * speedX * dt;
}

