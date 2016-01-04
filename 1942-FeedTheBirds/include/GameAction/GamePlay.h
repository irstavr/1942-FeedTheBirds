#ifndef GP_H
#define GP_H

#include "InputManager.h"
#include "../GameLogic/GameLogic.h"
#include "../Terrain/TerrainStartScreen.h"

#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h> 
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#define SCREEN_WINDOW_WIDTH  1460 
#define SCREEN_WINDOW_HEIGHT 669

#define GAME_STATE_INTRO 0
#define GAME_STATE_MAINGAME 1
#define GAME_STATE_PAUSED 2
#define GAME_STATE_GAMEOVER 3
#define GAME_STATE_FINISHED 4

#define FPS 20
#define LPS 10

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

	ALLEGRO_BITMAP *background ;
	ALLEGRO_TIMER *fpsTimer, *lpsTimer;
	ALLEGRO_FONT *font1, *font2;
	ALLEGRO_COLOR bright_green;
	const char* font_file = "..\\..\\data\\fonts\\karmatic_arcade_font.ttf";

	/* PARALLAX BG - MEIK GEIG*/
	ALLEGRO_BITMAP *bgImage = al_load_bitmap("..\\..\\data\\Bitmaps\\terrain\\sea1.png");
	ALLEGRO_BITMAP *mgImage = al_load_bitmap("..\\..\\data\\Bitmaps\\terrain\\sea2.png");
	ALLEGRO_BITMAP *fgImage = al_load_bitmap("..\\..\\data\\Bitmaps\\birdshit.png");

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
	/* get system current time */
	unsigned int getCurrTime();

	void displayStartScreen(unsigned long now);
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