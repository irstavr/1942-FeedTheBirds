#ifndef GP_H
#define GP_H

#include "InputManager.h"
#include "..\GameLogic\GameLogic.h"
#include "..\Terrain\TerrainStartScreen.h"
#include "..\Terrain\Terrain.h"
#include "..\Utilities\Utilities.h"

#define GAME_STATE_INTRO 0
#define GAME_STATE_MAINGAME 1
#define GAME_STATE_PAUSED 2
#define GAME_STATE_GAMEOVER 3
#define GAME_STATE_FINISHED 4

#define FPS 1
#define LPS 120

class GamePlay {
	GamePlay();

	std::string title;
	static GameLogic *currentGame;
	static float time, startTime, gamingTime, pauseTime;
	unsigned long currTime;

	const int windowHeight;
	const int windowWidth;

	/* Allegro initialization*/
	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE *eventQueue;
	ALLEGRO_EVENT alEvent;

	ALLEGRO_KEYBOARD_STATE keyboardState;

	ALLEGRO_TIMER *fpsTimer, *lpsTimer;

	clock_t wait;

	/* initialization */
	bool initAllegro();
	/* clear allegro */
	void cleanAllegro();
	/* runs the game loop*/
	void runMainLoop();
	/* clear all */
	void cleanGamePlay();
	/* inits engine of game - all classes instances */
	void initGameEngine();
	/* read from local input event queue */
	void inputManagement(ALLEGRO_EVENT);
	/*move in every frame*/
	bool frameFunc();
	/* game loop logic */
	void updateGameState();
	/*rander in every frame*/
	void render(unsigned long timestamp);
	/*init all*/
	void initGamePlay();
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

	void displayStartScreen(unsigned long now);
	void displayMainScreen(unsigned long now);

	/* updates game state and starts music */
	void gameStarting();

public:

	/* holds state of game (if in intro, game, gameover, exit) */
	int gameState;
	/* return the instance of the class*/
	static GamePlay *instance(bool newOne = false);
	/*start the window*/
	void start();

	~GamePlay();
};



#endif