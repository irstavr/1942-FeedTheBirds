#include "..\..\include\GameAction\GamePlay.h"

GamePlay::GamePlay() :
	title("anti1942 - StopWars"),
	gameState(GAME_STATE_INTRO),
	windowHeight(START_SCREEN_WINDOW_HEIGHT), 
	windowWidth(START_SCREEN_WINDOW_WIDTH) {
	powerUp = nullptr;
}

GamePlay *GamePlay::instance(bool newOne) {
	static GamePlay* gamegui = nullptr;
	if (!gamegui || newOne)
		gamegui = new GamePlay();
	return gamegui;
}

GamePlay::~GamePlay() {
}

void GamePlay::start() {
	initGamePlay();
}

void GamePlay::initGamePlay() {
	// init allegro
	if (!initAllegro()) {
		return;
	}
	// init game engine
	initGameEngine();
	// Main loop 
	runMainLoop();
	// Cleaning
	cleanGamePlay();
	cleanAllegro();
}

bool GamePlay::initAllegro() {

	if (!al_init()) {
		al_show_native_message_box(NULL, "Error", NULL, "Failed to initialize allegro!\n", NULL, NULL);
		return false;
	}

	if (!al_init_image_addon())
	{
		al_show_native_message_box(NULL, "Error!", "Image addon has failed to initialize.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	if (!al_install_keyboard()) ///setup the keyboard
	{
		al_show_native_message_box(NULL, "Error!", "Failed to install keyboard.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	fpsTimer = al_create_timer(1.0 / FPS);
	if (!fpsTimer) {
		al_show_native_message_box(NULL, "Error", NULL, "failed to create fpstimer!\n", NULL, NULL);
		return false;
	}
	
	lpsTimer = al_create_timer(1.0 / LPS);
	if (!lpsTimer) {
		al_show_native_message_box(NULL, "Error", NULL, "failed to create lpstimer!\n", NULL, NULL);
		return false;
	}

	al_set_new_window_position(100, 100);
	display = al_create_display(START_SCREEN_WINDOW_WIDTH, START_SCREEN_WINDOW_HEIGHT);
	if (!display) {
		al_show_native_message_box(NULL, "Error", NULL, "failed to create display!\n", NULL, NULL);
		al_destroy_timer(fpsTimer);
		al_destroy_timer(lpsTimer);
		return false;
	}

	if (!al_install_audio()) {
		al_show_native_message_box(NULL, "Error", NULL, "failed to initialize audio!\n", NULL, NULL);
		al_destroy_display(display);
		al_destroy_timer(fpsTimer);
		al_destroy_timer(lpsTimer);
		return false;
	}

	if (!al_init_acodec_addon()) {
		al_show_native_message_box(NULL, "Error", NULL, "failed to initialize audio codecs!\n", NULL, NULL);
		al_destroy_display(display);
		al_destroy_timer(fpsTimer);
		al_destroy_timer(lpsTimer);
		return false;
	}

	if (!al_reserve_samples(1)) {
		al_show_native_message_box(NULL, "Error", NULL, "failed to initialize audio codecs!\n", NULL, NULL);
		al_destroy_display(display);
		al_destroy_timer(fpsTimer);
		al_destroy_timer(lpsTimer);
		return false;
	}

	eventQueue = al_create_event_queue();
	if (!eventQueue) {
		al_show_native_message_box(NULL, "Error", NULL, "failed to create event_queue!\n", NULL, NULL);
		al_destroy_display(display);
		al_destroy_timer(fpsTimer);
		al_destroy_timer(lpsTimer);
		return false;
	}

	if (!al_init_primitives_addon()) {
		al_show_native_message_box(NULL, "Error", NULL, "failed to initialize primitives addon!\n", NULL, NULL);
		al_destroy_display(display);
		al_destroy_timer(fpsTimer);
		al_destroy_timer(lpsTimer);
		return false;
	}

	al_init_font_addon();
	al_init_ttf_addon();
	
	al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);

	//Tie events to queue
	al_register_event_source(eventQueue, al_get_display_event_source(display));
	al_register_event_source(eventQueue, al_get_keyboard_event_source());
	al_register_event_source(eventQueue, al_get_timer_event_source(fpsTimer));
	al_register_event_source(eventQueue, al_get_timer_event_source(lpsTimer));

	//Start timers 
	al_start_timer(lpsTimer);
	al_start_timer(fpsTimer);

	return true;
}

void GamePlay::initGameEngine() {
	// TODO
	// init all instances of these classes:
	// Logic
	// collisionChecker
	// AnimationFilmHolder
	// Background
	// etc.
	terrain = new Terrain();
	TerrainStartScreen::getInstance();
	ScoreBoard::getInstance();

	AnimationFilmHolder::initialize("1942-FeedTheBirds\\data\\films.ini");
	AnimationFilmHolder *animFH = AnimationFilmHolder::getSingleton();

	CollisionChecker::getInstance()->initialize();

	// Add start game button
	flashAnimation = new FlashingAnimation(1, 500, 500, 0);
	flashAnimator = new FlashingAnimator();
	AnimatorHolder::animRegister(flashAnimator); 
	
	startButton = new Button(160,
							 420, 
							(AnimationFilm *) 
								AnimationFilmHolder::getSingleton()->
									getFilm("StartButton"),
							flashAnimation,
							flashAnimator);

	pauseButton = new Button(200,
							420,
							(AnimationFilm *)
								AnimationFilmHolder::getSingleton()->
								getFilm("PauseButton"),
							flashAnimation->clone(0),
							flashAnimator->clone());

	gameOverButton = new Button(380, 
								350, 
								(AnimationFilm *)
									AnimationFilmHolder::getSingleton()->
										getFilm("GameOverButton"),
								flashAnimation->clone(1), 
								flashAnimator->clone());

	replayButton = new Button(380,
								440,
								(AnimationFilm *)
								AnimationFilmHolder::getSingleton()->
								getFilm("ReplayButton"),
								flashAnimation->clone(2),
								flashAnimator->clone());

	winButton = new Button(400,
							350,
							(AnimationFilm *)
							AnimationFilmHolder::getSingleton()->
							getFilm("WinButton"),
							flashAnimation->clone(3),
							flashAnimator->clone());

	// Characters - Items:

	// SuperAce

	deathAnimation = new FrameRangeAnimation(1, 8, 0, 0, 150, false, 4);
	deathAnimator = new FrameRangeAnimator();
	flyAnimation = new FrameRangeAnimation(1, 3, 0, 0, 100, true, 3);
	flyAnimator = new FrameRangeAnimator();

	takeOffAnimation = createTakeOffAnimation();
	takeOffAnimator = new MovingPathAnimator();
	landingAnimation = createLandingAnimation();
	landingAnimator = new MovingPathAnimator();

	loopAnimation = createLoopAnimation();
	loopAnimator = new MovingPathAnimator();

	AnimatorHolder::animRegister(loopAnimator);
	AnimatorHolder::animRegister(landingAnimator);
	AnimatorHolder::animRegister(deathAnimator);
	AnimatorHolder::animRegister(takeOffAnimator);
	AnimatorHolder::animRegister(flyAnimator);

	AudioHolder::initialize();
	AudioHolder::changeToSound("intro");
}

// loop animation for super ace when pressing A
MovingPathAnimation* GamePlay::createLandingAnimation() {
	std::list<PathEntry> paths;
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.30, 0, 90, 25));
	paths.splice(paths.end(), *createSmoothDiagonalPath(50, 0, 10));
	return new MovingPathAnimation(paths, 100);
}

MovingPathAnimation* GamePlay::createTakeOffAnimation() {
	std::list<PathEntry> paths;
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.30, 270, 360, 25));
	paths.splice(paths.end(), *createSmoothDiagonalPath(50, 0, 10));
	return new MovingPathAnimation(paths, 101);
}

// loop animation for super ace when pressing A
MovingPathAnimation* GamePlay::createLoopAnimation() {
	std::list<PathEntry> paths;
	paths.splice(paths.end(), *createCircularPath(SCREEN_WINDOW_WIDTH*0.10, 0, 360, littleGreyBirdSpeed));
	return new MovingPathAnimation(paths, 1);
}

void GamePlay::runMainLoop() {
	startButton->setVisibility(true);
	startButton->startFlashing();

	/* finish == exit of game */
	while (gameState != GAME_STATE_FINISHED) {
		currTime = getCurrTime();
		al_wait_for_event(eventQueue, &alEvent);

		/* read from local input event queue */
		inputManagement(alEvent);
		if (alEvent.timer.source == lpsTimer) {
			/* game loop logic */
			updateGameState();
		}
		/* draw screen */
		if(alEvent.timer.source == fpsTimer) 
			render(currTime);
	}
}

/* read from local input event queue */
void GamePlay::inputManagement(ALLEGRO_EVENT alEvent) {

	if (gameState != GAME_STATE_PAUSED) {
		switch (alEvent.type) {

		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			gameState = GAME_STATE_FINISHED;
			break;
		
		case ALLEGRO_EVENT_KEY_UP:
			switch (alEvent.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				if (gameState == GAME_STATE_MAINGAME)
					keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				if (gameState == GAME_STATE_MAINGAME)
					keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				if (gameState == GAME_STATE_MAINGAME)
					keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				if (gameState == GAME_STATE_MAINGAME)
					keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_ESCAPE:
				gameState = GAME_STATE_FINISHED;
				break;
			}
			break;
		case ALLEGRO_EVENT_KEY_DOWN:
			switch (alEvent.keyboard.keycode) 
			{
			case ALLEGRO_KEY_UP:
				if (gameState == GAME_STATE_MAINGAME)
					keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				if (gameState == GAME_STATE_MAINGAME)
					keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				if (gameState == GAME_STATE_MAINGAME)
					keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				if (gameState == GAME_STATE_MAINGAME)
					keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				if (gameState == GAME_STATE_MAINGAME)
					InputManager::shoot(currentGame, currentGame->superAce);
				break;
			case ALLEGRO_KEY_A:
				if (gameState == GAME_STATE_MAINGAME)
					InputManager::twist(currentGame->superAce);
				break;
			case ALLEGRO_KEY_P:
				pauseGame(currTime);
				//InputManager::pause(gameState);
				break;
			case ALLEGRO_KEY_S:
				if (gameState == GAME_STATE_INTRO) {
					InputManager::onKeyS(gameState, display, startButton);
					startNewGame();
				}
				break;
			case ALLEGRO_KEY_ENTER:
				if (gameState == GAME_STATE_GAMEOVER) {
					InputManager::onKeyEnter(gameState, display, startButton, gameOverButton);
					cleanGamePlay();
					hasWon = false;
				}
				break;
				/* O:  Just for our debugging*/
			case ALLEGRO_KEY_O:
				if (gameState == GAME_STATE_MAINGAME) {
					gameOver(currTime);
					break;
				}
			case ALLEGRO_KEY_ESCAPE:
				gameState = GAME_STATE_FINISHED;
				break;
			}		
		}
		InputManager::move(keys[UP], keys[DOWN], keys[LEFT], keys[RIGHT], currentGame->superAce);
	} 
	if (gameState == GAME_STATE_PAUSED && alEvent.keyboard.keycode == ALLEGRO_KEY_R) {
		resumeGame();
	}

}

/* game loop logic */
void GamePlay::updateGameState() {
	AnimatorHolder::progress(getCurrTime());
	
	if (gameState == GAME_STATE_MAINGAME) {
		// TODO
		// initialize:
		// AI
		// Animation progress
		// check if win
		// update scores/lives/etc on the display
		// etc 
		//
		checkAnimationFlags();
		checkBonuses();

		if (currentGame->superAce->isSuperAceDead()) {
			gameOver(getCurrTime());
		}
		CollisionChecker::getInstance()->check();
	}
}

void GamePlay::checkAnimationFlags() {

	if (currentGame->superAce->isInjured) {
		if (currentGame->superAce->injuredTime + 1200 < getCurrTime()) {
			currentGame->superAce->isInvincible = false;
			currentGame->superAce->isInjured = false;
		}
	}

	if (currentGame->superAce->isLooping) {
		if (currentGame->superAce->loopTime + 2000 < getCurrTime()) {
			currentGame->superAce->isInvincible = false;
			currentGame->superAce->isLooping = false;
		}
	}

	if (currentGame->superAce->isExploding) {
		if (currentGame->superAce->explosionTime + 1000 < getCurrTime()) {
			currentGame->superAce->setVisibility(false);
			currentGame->superAce->isExploding = false;
		}
	}

	if (currentGame->superAce->isLanding) {
		if (currentGame->superAce->landingTime + 1000 < getCurrTime()) {
			gameFinished();
		}
	}
	/*
	if (currentGame->superAce->isTakingOff) {
		if (currentGame->superAce->takeOffTime + 500 < getCurrTime()) {
			//changeSuperAceBitmap();
			currentGame->superAce->takeOffTime = 0;
			currentGame->superAce->enableMovement();
		}
	}
	*/
	// get here when super ace gets the pow 'no enemies bullets'
	if (currentGame->superAce->noEnemiesBullets) {
		if (currentGame->superAce->noEnemyBulletsTime + 1000 < getCurrTime()) {

			currentGame->superAce->noEnemiesBullets = false;

			for (std::vector<Bird*>::iterator it = currentGame->superAce->birds->begin(); it != currentGame->superAce->birds->end(); it++)
			{
				if (!(*it)->isDead())
					(*it)->canShoot = true;
			}
		}
	}

}

void GamePlay::checkBonuses() {

	if (currentGame->checkQuadGun) {
		if (currentGame->showBonus(quadGun)) {
			// show bitmap of POW
			displayPowerUp(quadGun);
			currentGame->checkQuadGun = false;
		}
	}
	if (currentGame->checkEnemyCrash) {
		if (currentGame->showBonus(enemyCrash)) {
			// show bitmap of POW
			displayPowerUp(enemyCrash);
			currentGame->checkEnemyCrash = false;
		}
	}
	if (currentGame->checkSideFighter) {
		if (currentGame->showBonus(sideFighters)) {
			// show bitmap of POW
			displayPowerUp(sideFighters);
			currentGame->checkSideFighter = false;
		}
	}
	if (currentGame->checkExtraLife) {
		if (currentGame->showBonus(extraLife)) {
			// show bitmap of POW
			displayPowerUp(extraLife);
			currentGame->checkExtraLife = false;
		}
	}
	if (currentGame->checkNoEnemyBullets) {
		if (currentGame->showBonus(noEnemyBullets)) {
			// show bitmap of POW
			displayPowerUp(noEnemyBullets);
			currentGame->checkNoEnemyBullets = false;
		}
	}
	if (currentGame->checkExtraLoop) {
		if (currentGame->showBonus(extraLoop)) {
			// show bitmap of POW
			displayPowerUp(extraLoop);
			currentGame->checkExtraLoop = false;
		}
	}
	if (currentGame->check1000Points) {
		if (currentGame->showBonus(points1000)) {
			// show bitmap of POW
			displayPowerUp(points1000);
			currentGame->check1000Points = false;
		}
	}
}

void GamePlay::render(unsigned long timestamp) {
	if (!al_is_event_queue_empty(eventQueue))
		return;
		
	if (gameState == GAME_STATE_INTRO) {
		displayStartScreen(timestamp);
	}
	if (gameState == GAME_STATE_MAINGAME) {
		displayMainScreen(timestamp);
	}
	if (gameState == GAME_STATE_GAMEOVER) {
		if(!hasWon)displayGameOver(timestamp);
		else displayGameFinished(timestamp);
	}
	if (gameState == GAME_STATE_PAUSED) {
		displayPauseGame(currTime);
	}
}

/* show first window with start screen */
void GamePlay::displayMainScreen(unsigned long now) {
	if (gameState == GAME_STATE_MAINGAME) {
		terrain->drawBackground(ScoreBoard::getInstance().getScore(),
								ScoreBoard::getInstance().getHighScore(),
								currentGame->profile->getLives(),
								currentGame->profile->getLoops());

		currentGame->superAce->displayAll();

		if (powerUp && powerUp->isSpriteVisible()) {
			powerUp->display(Rect(0, 0, 0, 0));
		}

		for (size_t i = 0; i < currentGame->birds->size(); i++) {
			currentGame->birds->at(i)->displayAll();
		}

		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
		terrain->updateBackground();
		
		checkActionPoints();

	}
}

/* show first window with start screen */
void GamePlay::displayStartScreen(unsigned long now) {
	TerrainStartScreen::getInstance().drawBackground();

	if (startButton->isSpriteVisible()) {
		startButton->display(Rect(0, 0, 0, 0));
	}

	al_flip_display();
	al_clear_to_color(al_map_rgb(0, 0, 0));
	TerrainStartScreen::getInstance().updateBackground();
}

void GamePlay::checkActionPoints() {
	ai->eventAtX(this->terrain->getTerrainX());
}

void GamePlay::pauseGame(unsigned long now) {
	if (gameState == GAME_STATE_MAINGAME) {
		gameState = GAME_STATE_PAUSED;
		AnimatorHolder::pause();
		pauseButton->startFlashing();
		pauseButton->setVisibility(true);
	}
}

void GamePlay::resumeGame(void) {
	gameState = GAME_STATE_MAINGAME;
	AnimatorHolder::resume();
	pauseButton->stopFlashing();
	pauseButton->setVisibility(false);
}

void GamePlay::gameOver(unsigned long now) {
	if (gameState != GAME_STATE_GAMEOVER) {
		gameState = GAME_STATE_GAMEOVER;
		currentGame->superAce->explode();
		AnimatorHolder::pauseAllExcept(deathAnimator);
		gameOverButton->startFlashing();
		//ScoreBoard::getInstance().setScore(0);
		currentGame->gameRunning = false;
		if(powerUp)
			powerUp->~PowerUp();
	}
}

void GamePlay::gameFinished() {
	if (gameState != GAME_STATE_GAMEOVER) {
		gameState = GAME_STATE_GAMEOVER;
		hasWon = true;
		winButton->setVisibility(true);
		currentGame->gameRunning = false;
		powerUp->~PowerUp();
	}
}

void GamePlay::displayPowerUp(PowerUpType_t powerUpID)
{
	powerUp = new PowerUp(400, 200, powerUpID,
						  (AnimationFilm *)
							AnimationFilmHolder::getSingleton()->
								getFilm(powerUpToString(powerUpID)));
	CollisionChecker::getInstance()->
					registerCollisions(currentGame->superAce, powerUp);
	powerUp->setVisibility(true);
}

inline std::string GamePlay::powerUpToString(PowerUpType_t v)
{
	switch (v)
	{
	case quadGun:   return "quadGun";
	case enemyCrash:   return "enemyCrash";
	case sideFighters: return "sideFighters";
	case extraLife:   return "extraLife";
	case noEnemyBullets:   return "noEnemyBullets";
	case extraLoop: return "extraLoop";
	case points1000: return "points1000";
	default:  return "[Unknown PowerUpType]";
	}
}

void GamePlay::displayGameFinished(unsigned long now) {
	terrain->drawBackground(ScoreBoard::getInstance().getScore(),
		ScoreBoard::getInstance().getHighScore(),
		currentGame->profile->getLives(),
		currentGame->profile->getLoops());
	currentGame->superAce->displayAll();
	winButton->display(Rect(0, 0, 0, 0));
	replayButton->display(Rect(0, 0, 0, 0));

	al_flip_display();
	al_clear_to_color(al_map_rgb(0, 0, 0));
}

void GamePlay::displayGameOver(unsigned long now) {
	terrain->drawBackground(ScoreBoard::getInstance().getScore(),
		ScoreBoard::getInstance().getHighScore(),
		currentGame->profile->getLives(),
		currentGame->profile->getLoops());
	currentGame->superAce->displayAll();
	if (gameOverButton->isSpriteVisible()) {
		gameOverButton->display(Rect(0, 0, 0, 0));
	}
	replayButton->display(Rect(0, 0, 0, 0));

	al_flip_display();
	al_clear_to_color(al_map_rgb(0, 0, 0));
}

void GamePlay::displayPauseGame(unsigned long now) {
	terrain->drawBackground(ScoreBoard::getInstance().getScore(),
		ScoreBoard::getInstance().getHighScore(),
		currentGame->profile->getLives(),
		currentGame->profile->getLoops());

	if (pauseButton->isSpriteVisible()) {
		pauseButton->setX(600);
		pauseButton->setY(300);
		pauseButton->display(Rect(0, 0, 0, 0));
	}
	al_flip_display();
	al_clear_to_color(al_map_rgb(0, 0, 0));
}

void GamePlay::startNewGame() {
	gameState = GAME_STATE_MAINGAME;
	AudioHolder::stop();
	
	currentGame = new GameLogic(takeOffAnimation,
								takeOffAnimator,
								landingAnimation,
								landingAnimator,
								deathAnimation,
								deathAnimator,
								loopAnimation,
								loopAnimator);


	terrain = new Terrain();
	ScoreBoard::getInstance().setScore(0);
	keys[UP] = false;
	keys[DOWN] = false;
	keys[LEFT] = false;
	keys[RIGHT] = false;

	ai = new AI(currentGame, flyAnimator, flyAnimation);
	currentGame->superAce->startTakeOff();
	displayMainScreen(getCurrTime());
}

void GamePlay::cleanGamePlay() {
	// TODO: clean all instances of all the classes!
	//
	if (gameState != GAME_STATE_INTRO) {

		currentGame->cleanUp();
		currentGame->superAce->cleanUp();
		ai->cleanUp();
		CollisionChecker::getInstance()->cleanUp();
	}
}

void GamePlay::cleanAllegro() {
	AnimationFilmHolder::destroy();
	al_destroy_timer(lpsTimer);
	al_destroy_timer(fpsTimer);
	al_destroy_display(display);
	al_destroy_event_queue(eventQueue);
}

void GamePlay::reset() {
	//TODO next version
}

void GamePlay::save() {
	//TODO next version
}

void GamePlay::saveRep() {
	//TODO next version
}

void GamePlay::load() {
	//TODO next version
}

void GamePlay::loadRep() {
	//TODO next version
}