#include "..\..\include\GameLogic\GameLogic.h"

GameLogic::GameLogic (FrameRangeAnimation *takeOffAnimation,
					  FrameRangeAnimator *takeOffAnimator,
					  FrameRangeAnimation *landingAnimation,
					  FrameRangeAnimator *landingAnimator,
					  FrameRangeAnimation *deathAnimation,
					  FrameRangeAnimator *deathAnimator,
					  FrameRangeAnimation *flyAnimation,
					  FrameRangeAnimator *flyAnimator) :
		gameRunning(true),
		highScore(0) {
	profile = new PlayerProfile(std::make_pair(0,0));
	superAce = new SuperAce(profile,
							200,
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

	Bird *bird = new Bird(1000, 500,
						(AnimationFilm*)
							AnimationFilmHolder::getSingleton()->
								getFilm("bonusBird"),
						flyAnimation,
						flyAnimator);

	birds = new vector<Bird*>();
	birds->push_back(bird);
}

GameLogic::~GameLogic() {
	gameRunning = 0;
	superAceKilled = 1;
	highScore = 0;
}

bool GameLogic::isRunning() const {
	return gameRunning;
}

int GameLogic::solveCollision() {
	return 0;
}