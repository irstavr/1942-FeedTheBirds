#include "..\..\..\include\Objects\Items\Button.h"

Button::Button(int _x, int _y,
			AnimationFilm *film,
			FlashingAnimation *_anim, 
			FlashingAnimator *_animator) :
	Sprite(_x, _y, film), anim(_anim), animator(_animator) {
}

void Button::startFlashing(void) {
	anim->setRepetitions(0);
	animator->start(this, anim, getCurrTime());
	AnimatorHolder::markAsRunning(animator);
}

void Button::stopFlashing(void) {
	AnimatorHolder::markAsSuspended(animator);
	AnimatorHolder::cancel(animator);
}