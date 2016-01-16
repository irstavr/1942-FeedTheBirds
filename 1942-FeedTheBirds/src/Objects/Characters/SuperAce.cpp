#include "..\..\..\include\Objects\Characters\SuperAce.h"

SuperAce::SuperAce(Dim _x, Dim _y, AnimationFilm* film,
	FrameRangeAnimation *_takeOffAnimation, 
	FrameRangeAnimator *_takeOffAnimator,
	FrameRangeAnimation *_landAnimation, 
	FrameRangeAnimator *_landAnimator,
	FrameRangeAnimation *_deathAnimation, 
	FrameRangeAnimator *_deathAnimator) :
	Sprite(_x, _y, film),
	takeOffAnimation(_takeOffAnimation), 
	takeOffAnimator(_takeOffAnimator),
	landAnimation(_landAnimation), 
	landAnimator(_landAnimator),
	deathAnimation(_deathAnimation), 
	deathAnimator(_deathAnimator) {
	isInvisible = false;
	isShooting = false;
}

SuperAce::~SuperAce(void) {
	isInvisible = true;
	isShooting = false;

}

void SuperAce::moveUp() {
	//cout << "moveUp\n";
	if (y>10) {
		y -= 10;
	}
	//cout << "y " << y << "\n";
	//cout << "x " << x << "\n";
}

void SuperAce::moveDown() {
	//cout << "movedown\n";
	if (y < SCREEN_WINDOW_HEIGHT - 120) {
		y += 10;
	}
	//cout << "y " << y << "\n";
	//cout << "x " << x << "\n";
}

void SuperAce::moveLeft() {
	//cout << "moveleft\n";
	if (x > 10) {
		x -= 10;
	}
	//cout << "y " << y << "\n";
	///cout << "x " << x << "\n";
}

void SuperAce::moveRight() {
	//cout << "moveright\n";
	if (x < SCREEN_WINDOW_WIDTH/2) {
		x += 10;
	}
	//cout << "y " << y << "\n";
	//cout << "x " << x << "\n";
}

void SuperAce::die() {

}