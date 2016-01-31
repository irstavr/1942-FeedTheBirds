#include "..\..\include\GameLogic\GameLogic.h"

GameLogic::GameLogic (FrameRangeAnimation *takeOffAnimation,
					  FrameRangeAnimator *takeOffAnimator,
					  MovingPathAnimation *landingAnimation,
					  MovingPathAnimator *landingAnimator,
					  FrameRangeAnimation *deathAnimation,
					  FrameRangeAnimator *deathAnimator,
					  MovingPathAnimation* loopAnimation,
					  MovingPathAnimator* loopAnimator) {
	gameRunning = true;
	superAceKilled = false;
	profile = new PlayerProfile(std::make_pair(0,0));

	birds = new vector<Bird*>();
	superAce = new SuperAce(profile,
							100,
							285,
							(AnimationFilm*)
								AnimationFilmHolder::getSingleton()->
									getFilm("takeOff"),
							takeOffAnimation,
							takeOffAnimator,
							landingAnimation,
							landingAnimator,
							deathAnimation,
							deathAnimator,
							loopAnimation,
							loopAnimator,
		                    this->birds);
}

GameLogic::~GameLogic() {
	gameRunning = false;
	superAceKilled = true;
}

Bird* GameLogic::createBird(Dim _x, Dim _y, 
							BirdID birdID,
							BirdLives birdLives,
							BirdSpeed birdSpeed,
							BirdFire birdFire,
							char* filmId,
							FrameRangeAnimation *flyAnimation,
							FrameRangeAnimator *flyAnimator) {
	Bird *bird = new Bird(_x, _y, 
						  birdID,
						  birdLives,
						  birdSpeed,
						  birdFire,
						  (AnimationFilm*)
								AnimationFilmHolder::getSingleton()->
									getFilm(filmId),
										flyAnimation,
										flyAnimator);

	birds->push_back(bird);
	bird->startMoving();

	CollisionChecker::getInstance()->
					registerCollisions(superAce, bird);

	return bird;
}

bool GameLogic::isRunning() const {
	return gameRunning;
}

int GameLogic::solveCollision() {
	return 0;
}