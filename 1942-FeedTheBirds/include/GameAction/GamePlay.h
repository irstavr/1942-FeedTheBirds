#ifndef GP_H
#define GP_H

#include "../GameLogic/GameLogic.h"


#define GAME_STATE_INTRO 0
#define GAME_STATE_MAINGAME 1
#define GAME_STATE_PAUSED 2
#define GAME_STATE_GAMEOVER 3
#define GAME_STATE_FINISHED 4

class GamePlay {
	std::string title;
	GameLogic *currentGame;
	float time, startTime, gamingTime, pauseTime;

	const int windowHeight;
	const int windowWidth;

	/*create the signal pressed by user*/
	bool getSignal();
	/*move in every frame*/
	static bool FrameFunc();
	/*rander in every frame*/
	static bool RenderFunc();
	/*init all*/
	void gamePlayInit();
	/*renew all stuff*/
	void reset();
	/*save*/
	void save();
	/*load*/
	void load();
	/*save replay*/
	void saveRep();
	/*load replay*/
	void loadRep();

	GamePlay();

public:

	int gameState;
	/*return the instance of the class*/
	static GamePlay *instance(bool newOne = false);
	/*start the window*/
	void start();

	~GamePlay();
};



#endif