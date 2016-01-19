#include "..\..\include\GameLogic\GameLogic.h"

GameLogic::GameLogic (FrameRangeAnimation *takeOffAnimation,
					  FrameRangeAnimator *takeOffAnimator,
					  FrameRangeAnimation *landingAnimation,
					  FrameRangeAnimator *landingAnimator,
					  FrameRangeAnimation *deathAnimation,
					  FrameRangeAnimator *deathAnimator) :
		gameRunning(true),
		highScore(0) {
	profile = new PlayerProfile(std::make_pair(5,5));
	superAce = new SuperAce(200,
							300,
							(AnimationFilm*)
								AnimationFilmHolder::getSingleton()->
									getFilm("superAce"),
							takeOffAnimation,
							takeOffAnimator,
							landingAnimation,
							landingAnimator,
							deathAnimation,
							deathAnimator);
	//birds = 
}

GameLogic::~GameLogic()
{
	//delete superAce;
	//delete birds;
	//delete profile;
	gameRunning = 0;
	superAceKilled = 1;
	highScore = 0;
}

bool GameLogic::isRunning() const {
	return gameRunning;
}
