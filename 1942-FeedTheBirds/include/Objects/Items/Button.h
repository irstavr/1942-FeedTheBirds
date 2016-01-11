#ifndef _BUTTON_H
#define _BUTTON_H

#include "..\..\Sprites\Sprite.h"
#include "..\..\Animation\FlashingAnimation.h"
#include "..\..\Animator\FlashingAnimator.h"
#include "..\..\Animator\AnimatorHolder.h"
#include "..\..\Utilities\Utilities.h"

class Button : public Sprite {
private:
	FlashingAnimation *anim;
	FlashingAnimator *animator;

public:
	Button(int _x, int _y, AnimationFilm *film, FlashingAnimation *_anim, FlashingAnimator *_animator);

	virtual void resetToDefaultFilm(void) {}; //no need to implement in current game
	
	void startFlashing(void);

	void stopFlashing(void);
};

#endif