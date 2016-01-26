#include "..\..\include\GameLogic\GameLogic.h"

GameLogic::GameLogic (FrameRangeAnimation *takeOffAnimation,
					  FrameRangeAnimator *takeOffAnimator,
					  FrameRangeAnimation *landingAnimation,
					  FrameRangeAnimator *landingAnimator,
					  FrameRangeAnimation *deathAnimation,
					  FrameRangeAnimator *deathAnimator):
		gameRunning(true),
		highScore(0) {
	profile = new PlayerProfile(std::make_pair(0,0));
	superAce = new SuperAce(profile,
							100,
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

	birds = new vector<Bird*>();
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

void GameLogic::createBird(Dim _x, Dim _y, char* filmId,
	FrameRangeAnimation *flyAnimation,
	FrameRangeAnimator *flyAnimator) {
	Bird *bird = new Bird(_x, _y,
		(AnimationFilm*)
		AnimationFilmHolder::getSingleton()->
		getFilm(filmId),
		flyAnimation,
		flyAnimator);

	birds->push_back(bird);

	bird->startMoving();
	CollisionChecker::getInstance()->
		registerCollisions(superAce, bird);
}

bool GameLogic::isRunning() const {
	return gameRunning;
}

int GameLogic::solveCollision() {
	return 0;
}