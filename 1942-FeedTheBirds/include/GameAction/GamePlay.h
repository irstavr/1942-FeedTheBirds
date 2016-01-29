#ifndef GP_H
#define GP_H

#include "..\GameLogic\GameLogic.h"
#include "..\Terrain\TerrainStartScreen.h"
#include "..\Terrain\Terrain.h"
#include "..\Utilities\Utilities.h"
#include "..\Animation\AnimationFilmHolder.h"
#include "..\Objects\Items\Button.h"
#include "..\Animation\FlashingAnimation.h"
#include "..\Animator\FrameRangeAnimator.h"
#include "..\Animator\FlashingAnimator.h"
#include "..\Animator\MovingPathAnimator.h"
#include "..\Animator\AnimatorHolder.h"
#include "..\Objects\Characters\SuperAce.h"
#include "AI.h"
#include "InputManager.h"
#include "CollisionChecker.h"

enum KEYS { UP, DOWN, LEFT, RIGHT };

class GamePlay {

public:
	GamePlay();
	~GamePlay();

	GameLogic *currentGame;

	/* holds state of game (if in intro, game, gameover, exit) */
	int gameState;
	MovingAnimation *bulletAnimation;
	MovingAnimator *bulletAnimator;

	/* return the instance of the class*/
	static GamePlay *instance(bool newOne = false);
	/*start the window*/
	void start();

private:

	std::string title;
	static float time, startTime, gamingTime, pauseTime;
	unsigned long currTime;

	const int windowHeight;
	const int windowWidth;

	AI *ai;
	Terrain* terrain;

	/* Allegro initialization*/
	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE *eventQueue;
	ALLEGRO_EVENT alEvent;
	ALLEGRO_KEYBOARD_STATE keyboardState;
	ALLEGRO_TIMER *fpsTimer, *lpsTimer;

	clock_t wait;

	/* for graphics */
	Button *startButton, *pauseButton, *winButton, *gameOverButton;

	bool keys[4] = { false, false, false, false };
	unsigned int actionPoint;
	FrameRangeAnimation *takeOffAnimation;
	FrameRangeAnimator *takeOffAnimator;
	FrameRangeAnimation *landingAnimation;
	FrameRangeAnimator *landingAnimator;
	FrameRangeAnimation *deathAnimation;
	FrameRangeAnimator *deathAnimator;
	FrameRangeAnimation *flyAnimation;
	FrameRangeAnimator *flyAnimator;
	MovingPathAnimation* loopAnimation;
	MovingPathAnimator* loopAnimator;

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

	/* updates game state and starts music */
	void startNewGame();
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
	void checkActionPoints();
	void pauseGame(unsigned long now);
	void gameOver(unsigned long now);
	void resumeGame(void);

	MovingPathAnimation* createSmallBirdAnimation();
	MovingPathAnimation *createLoopAnimation(void);
};
#endif