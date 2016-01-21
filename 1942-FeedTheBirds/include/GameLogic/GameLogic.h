#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <vector>

#include "PlayerProfile.h"
#include "..\Sprites\Sprite.h"
#include "..\Objects\Items\Fish.h"
#include "..\Objects\Characters\Bird.h"
#include "..\Objects\Characters\SuperAce.h"

typedef vector<Bird*> BIRDS;

class GameLogic {
public:

	BIRDS *birds;
	PlayerProfile* profile;
	SuperAce* superAce;

public:
	GameLogic(FrameRangeAnimation *takeOffAnimation,
				FrameRangeAnimator *takeOffAnimator,
				FrameRangeAnimation *landingAnimation,
				FrameRangeAnimator *landingAnimator,
				FrameRangeAnimation *deathAnimation,
				FrameRangeAnimator *deathAnimator,
				FrameRangeAnimation *flyAnimation,
				FrameRangeAnimator *flyAnimator);
	~GameLogic();


	int height, width, superAceKilled;
	bool gameRunning;
	
	Points highScore;

	/*solve all the outrange stuff*/
	void solveOutRange();
	/*solve all the collision stuff*/
	int solveCollision();
	/*return if the game is still running*/
	bool isRunning() const;
	void clearUp();
};

#endif