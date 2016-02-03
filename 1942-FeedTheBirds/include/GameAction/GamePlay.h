#ifndef GP_H
#define GP_H

#include "..\GameLogic\GameLogic.h"
#include "..\GameLogic\ScoreBoard.h"
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
#include "AudioHolder.h"
#include "AI.h"
#include "InputManager.h"
#include "CollisionChecker.h"

enum KEYS { UP, DOWN, LEFT, RIGHT };

class GamePlay {

public:
	GamePlay();
	~GamePlay();

	// deleted function to make sure they are unacceptable
	// in order to be sure we dont get copies of the singleton
	GamePlay(GamePlay const&) = delete;
	void operator=(GamePlay const&) = delete;

	GameLogic *currentGame;
	PowerUp* powerUp;

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
	bool hasWon = false;
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
	Button *startButton, *pauseButton, *winButton, *gameOverButton, *replayButton;

	bool keys[4] = { false, false, false, false };
	unsigned int actionPoint;
	FlashingAnimation *flashAnimation;
	FlashingAnimator *flashAnimator;
	FrameRangeAnimation *takeOffAnimation;
	FrameRangeAnimator *takeOffAnimator;
	FrameRangeAnimation *deathAnimation;
	FrameRangeAnimator *deathAnimator;
	FrameRangeAnimation *flyAnimation;
	FrameRangeAnimator *flyAnimator;
	MovingPathAnimation* loopAnimation;
	MovingPathAnimator* loopAnimator;
	MovingPathAnimation* landingAnimation;
	MovingPathAnimator* landingAnimator;

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
	MovingPathAnimation * createLandingAnimation();
	/* read from local input event queue */
	void inputManagement(ALLEGRO_EVENT);
	void checkAnimationFlags();
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
	void displayPauseGame(unsigned long now);
	void displayGameOver(unsigned long now);
	void displayGameFinished(unsigned long now);
	void checkActionPoints();
	void checkBonuses();
	void pauseGame(unsigned long now);
	void gameOver(unsigned long now);
	void resumeGame(void);
	void gameFinished(void);
	void displayPowerUp(PowerUpType_t powerUpID);

	MovingPathAnimation *createLoopAnimation(void);

	inline std::string powerUpToString(PowerUpType_t v);
};
#endif