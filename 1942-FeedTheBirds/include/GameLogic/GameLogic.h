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
#include "..\Objects\Items\PowerUp.h"

typedef vector<Bird*> BIRDS;

class GameLogic {
public:
	GameLogic(MovingPathAnimation *takeOffAnimation,
			MovingPathAnimator *takeOffAnimator,
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

	BIRDS *bonusPow1Birds;	//used to release the POW1
	BIRDS *bonusPow2Birds;	//used to release the POW2
	BIRDS *bonusPow3Birds;	//used to release the POW3
	BIRDS *bonusPow4Birds;	//used to release the POW4
	BIRDS *bonusPow5Birds;	//used to release the POW5
	BIRDS *bonusPow6Birds;	//used to release the POW6
	BIRDS *bonusPow7Birds;	//used to release the POW7

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

	bool showBonus(PowerUpType_t bonus);
	void addBonusBirdToList(PowerUpType_t powID, Bird* bird);

private:
	/*return if the game is still running*/
	bool isRunning() const;

};

#endif