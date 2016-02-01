#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <vector>
#include <iostream>
#include "ScoreBoard.h"
#include "PlayerProfile.h"
#include "..\Sprites\Sprite.h"
#include "..\Objects\Items\Fish.h"
#include "..\Objects\Characters\Bird.h"
#include "..\Objects\Characters\SuperAce.h"

typedef vector<Bird*> BIRDS;

// used in order to discriminate birds
// and count user's score when feeds them
enum BonusID {
	quadGun = 0,
	enemyCrash,
	sideFighter,
	extraLife,
	noEnemyBullets,
	extraLoop,
	points1000
};

class GameLogic {
public:
	GameLogic(FrameRangeAnimation *takeOffAnimation,
			FrameRangeAnimator *takeOffAnimator,
			MovingPathAnimation *landingAnimation,
			MovingPathAnimator *landingAnimator,
			FrameRangeAnimation *deathAnimation,
			FrameRangeAnimator *deathAnimator,
			MovingPathAnimation* loopAnimation,
			MovingPathAnimator* loopAnimator);
	~GameLogic();

	Bird * createBird(Dim _x, Dim _y, 
					BirdID birdID, 
					BirdLives birdLives, 
					BirdSpeed birdSpeed, 
					BirdFire birdFire,
					char * filmId, 
					FrameRangeAnimation * flyAnimation, 
					FrameRangeAnimator * flyAnimator);

	BIRDS *birds;
	BIRDS *bonusBirds;	//used to release the POWS

	PlayerProfile* profile;
	SuperAce* superAce;
	Sprite* explosion;
	ScoreBoard* scoreBoard;

	bool superAceKilled, gameRunning;

	// flags for checking bonuses
	// used from AI to inform logic to check bonus birds list
	// and if list is empty (all birds are fed) then
	// set the accordinate 'show' flag to true
	bool checkQuadGun;
	bool checkEnemyCrash;
	bool checkSideFighter;
	bool checkExtraLife;
	bool checkNoEnemyBullets;
	bool checkExtraLoop;
	bool check1000Points;

	// bonuses
	// used to inform game play to show the POW
	bool showQuadGun;
	bool showEnemyCrash;
	bool showSideFighter;
	bool showExtraLife;
	bool showNoEnemyBullets;
	bool showExtraLoop;
	bool show1000Points;

	bool showBonus(BonusID bonus);

private:
	/*return if the game is still running*/
	bool isRunning() const;

};

#endif