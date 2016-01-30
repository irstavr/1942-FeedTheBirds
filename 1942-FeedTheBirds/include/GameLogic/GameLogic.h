#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <vector>

#include "ScoreBoard.h"
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
	Sprite* explosion;
	ScoreBoard* scoreBoard;

	bool superAceKilled, gameRunning;
	GameLogic(FrameRangeAnimation *takeOffAnimation,
			FrameRangeAnimator *takeOffAnimator,
			MovingPathAnimation *landingAnimation,
			MovingPathAnimator *landingAnimator,
			FrameRangeAnimation *deathAnimation,
			FrameRangeAnimator *deathAnimator,
			MovingPathAnimation* loopAnimation,
			MovingPathAnimator* loopAnimator);
	~GameLogic();

	Bird * createBird(Dim _x, Dim _y, BirdID birdID, BirdLives birdLives, BirdSpeed birdSpeed, char * filmId, FrameRangeAnimation * flyAnimation, FrameRangeAnimator * flyAnimator);

private:
	/*solve all the collision stuff*/
	int solveCollision();
	/*return if the game is still running*/
	bool isRunning() const;

};

#endif