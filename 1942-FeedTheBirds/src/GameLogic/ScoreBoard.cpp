#include "../../include/GameLogic/ScoreBoard.h"

// constructors
ScoreBoard::ScoreBoard() {
	score = 0;
	highScore = 0;
}

// destructor
ScoreBoard::~ScoreBoard() {
	score = 0;
	highScore = 0;
}

// get instance of singleton class
ScoreBoard& ScoreBoard::getInstance() {
	static ScoreBoard instance;
	return instance;
}

// increase game score
void ScoreBoard::incrScore(Score addedPoints) {
	assert(addedPoints >= 0);
	score += addedPoints;
	if (highScore < score) {
		highScore = score;
	}
}

// set score of game
void ScoreBoard::setScore(Score newScore) {
	score = newScore; 
}

// get game's score
Score ScoreBoard::getScore(void) {
	return score; 
}

// increase HighScore
void ScoreBoard::incrHighScore(HighScore addedPoints) {
	assert(addedPoints >= 0);
	highScore += addedPoints;
}

// set high score
void ScoreBoard::setHighScore(HighScore newScore) {
	highScore = newScore;
}

// get high score
HighScore ScoreBoard::getHighScore(void) {
	return highScore;
}