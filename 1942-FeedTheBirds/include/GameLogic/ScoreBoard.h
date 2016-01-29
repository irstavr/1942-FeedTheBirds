#ifndef SCORE_BOARD_H
#define SCORE_BOARD_H

//#include <stdio.h>
//#include <allegro5/allegro.h>
#include "../../include/Utilities/Utilities.h"

typedef int Score;
typedef int HighScore;

class ScoreBoard {
public:
	static ScoreBoard& getInstance();

	void incrScore(Score addedPoints);
	void setScore(Score newScore);
	Score getScore(void);

	void incrHighScore(HighScore addedPoints);
	void setHighScore(HighScore newScore);
	HighScore getHighScore(void);

private:
	ScoreBoard();
	~ScoreBoard();

	// deleted function to make sure they are unacceptable
	// in order to be sure we dont get copies of the singleton
	ScoreBoard(ScoreBoard const&) = delete;
	void operator=(ScoreBoard const&) = delete;

	Score score;
	HighScore highScore;
};
#endif