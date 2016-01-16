#include "..\..\..\include\Objects\Characters\SuperAce.h"

SuperAce::SuperAce(Dim _x, Dim _y, AnimationFilm* film,
	FrameRangeAnimation *_takeOffAnimation, FrameRangeAnimator *_takeOffAnimator,
	FrameRangeAnimation *_landAnimation, FrameRangeAnimator *_landAnimator,
	FrameRangeAnimation *_deathAnimation, FrameRangeAnimator *_deathAnimator) :
	Sprite(_x, _y, film),
	takeOffAnimation(_takeOffAnimation), takeOffAnimator(_takeOffAnimator),
	landAnimation(_landAnimation), landAnimator(_landAnimator),
	deathAnimation(_deathAnimation), deathAnimator(_deathAnimator) {
	isInvisible = false;
	isShooting = false;
}

SuperAce::~SuperAce(void) {
}

void SuperAce::moveUp() {
	//cout << "moveUp\n";
	y -= 10;
	//cout << "y " << y << "\n";
	//cout << "x " << x << "\n";
}

void SuperAce::moveDown() {
	//cout << "movedown\n";
	y += 10;
	//cout << "y " << y << "\n";
	//cout << "x " << x << "\n";
}

void SuperAce::moveLeft() {
	//cout << "moveleft\n";
	x -= 10;
	//cout << "y " << y << "\n";
	///cout << "x " << x << "\n";
}

void SuperAce::moveRight() {
	//cout << "moveright\n";
	x += 10;
	//cout << "y " << y << "\n";
	//cout << "x " << x << "\n";
}