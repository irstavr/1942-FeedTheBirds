#ifndef GP_H
#define GP_H

#include "../GameLogic/GameLogic.h"
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h> 
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define SCREEN_WINDOW_WIDTH  1460 
#define SCREEN_WINDOW_HEIGHT 669

#define GAME_STATE_INTRO 0
#define GAME_STATE_MAINGAME 1
#define GAME_STATE_PAUSED 2
#define GAME_STATE_GAMEOVER 3
#define GAME_STATE_FINISHED 4

#define FPS 4
#define LPS 1

class GamePlay {
	std::string title;
	GameLogic *currentGame;
	float time, startTime, gamingTime, pauseTime;

	const int windowHeight;
	const int windowWidth;

	/* Allegro initialization*/
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *eventQueue = NULL;
	ALLEGRO_EVENT alEvent;
	ALLEGRO_BITMAP *background = NULL;
	ALLEGRO_TIMER *fpsTimer = NULL, *lpsTimer = NULL;
	ALLEGRO_FONT *font1, *font2;
	ALLEGRO_COLOR bright_green;

	const char* font_file = "karmatic_arcade_font.ttf";

	/* initialization */
	bool initAllegro();
	/* clear allegro */
	void cleanAllegro();
	/* runs the game loop*/
	void runMainLoop();

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