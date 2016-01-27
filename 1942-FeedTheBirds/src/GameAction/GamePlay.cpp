#include "..\..\include\GameAction\GamePlay.h"

GamePlay::GamePlay() :
	title("anti1942 - StopWars"),
	gameState(GAME_STATE_INTRO),
	windowHeight(START_SCREEN_WINDOW_HEIGHT), 
	windowWidth(START_SCREEN_WINDOW_WIDTH)
{
	//time(-1), startTime(0),
	//musicOn(false), pauseTime(-1.5), colorB(false) {
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
	/*
	lpsTimer = al_create_timer(1.0 / LPS);
	if (!lpsTimer) {
		al_show_native_message_box(NULL, "Error", NULL, "failed to create lpstimer!\n", NULL, NULL);
		return false;
	}
	*/

	display = al_create_display(START_SCREEN_WINDOW_WIDTH, START_SCREEN_WINDOW_HEIGHT);
	if (!display) {
		al_show_native_message_box(NULL, "Error", NULL, "failed to create display!\n", NULL, NULL);
		al_destroy_timer(fpsTimer);
		//al_destroy_timer(lpsTimer);
		return false;
	}
	al_set_new_window_position(0, 0);

	if (!al_install_audio()) {
		al_show_native_message_box(NULL, "Error", NULL, "failed to initialize audio!\n", NULL, NULL);
		al_destroy_display(display);
		al_destroy_timer(fpsTimer);
		//al_destroy_timer(lpsTimer);
		return false;
	}

	if (!al_init_acodec_addon()) {
		al_show_native_message_box(NULL, "Error", NULL, "failed to initialize audio codecs!\n", NULL, NULL);
		al_destroy_display(display);
		al_destroy_timer(fpsTimer);
		//al_destroy_timer(lpsTimer);
		return false;
	}

	eventQueue = al_create_event_queue();
	if (!eventQueue) {
		al_show_native_message_box(NULL, "Error", NULL, "failed to create event_queue!\n", NULL, NULL);
		al_destroy_display(display);
		al_destroy_timer(fpsTimer);
		//al_destroy_timer(lpsTimer);
		return false;
	}

	if (!al_init_primitives_addon()) {
		al_show_native_message_box(NULL, "Error", NULL, "failed to initialize primitives addon!\n", NULL, NULL);
		al_destroy_display(display);
		al_destroy_timer(fpsTimer);
		//al_destroy_timer(lpsTimer);
		return false;
	}

	al_init_font_addon();
	al_init_ttf_addon();
	
	al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);

	//Tie events to queue
	al_register_event_source(eventQueue, al_get_display_event_source(display));
	al_register_event_source(eventQueue, al_get_keyboard_event_source());
	al_register_event_source(eventQueue, al_get_timer_event_source(fpsTimer));
	//al_register_event_source(eventQueue, al_get_timer_event_source(lpsTimer));

	//Start timers 
	//al_start_timer(lpsTimer);
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
	TerrainStartScreen::getInstance();
	AnimationFilmHolder::initialize("1942-FeedTheBirds\\data\\films.ini");
	AnimationFilmHolder *animFH = AnimationFilmHolder::getSingleton();

	CollisionChecker::getInstance()->initialize();

	// Add start game button
	FlashingAnimation *flashAnimation = new FlashingAnimation(1, 500, 500, 0);
	FlashingAnimator *flashAnimator = new FlashingAnimator();
	AnimatorHolder::animRegister(flashAnimator); 
	
	startButton = new Button(150,
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
							flashAnimation,
							flashAnimator);

	gameOverButton = new Button(500, 
								380, 
								(AnimationFilm *)
									AnimationFilmHolder::getSingleton()->
										getFilm("GameOverButton"),
								flashAnimation, 
								flashAnimator);

	// replay button ?


	// Characters - Items:

	// SuperAce
	// add take off, landing, explosion(?) bbs
	int total_frames = AnimationFilmHolder::getSingleton()->getFilm("bonusBird")->getTotalFrames();
	landingAnimation = new FrameRangeAnimation(1, 3, 0, 0, 200, false, 1);
	landingAnimator = new FrameRangeAnimator();
	takeOffAnimation = new FrameRangeAnimation(1, 3, 0, 0, 200, false, 2);
	takeOffAnimator = new FrameRangeAnimator();
	deathAnimation = new FrameRangeAnimation(1, 6, 0, 0, 200, false, 4);
	deathAnimator = new FrameRangeAnimator();
	flyAnimation = new FrameRangeAnimation(1, 3, -5, -5, 200, true, 3);
	flyAnimator = new FrameRangeAnimator();

	//bulletAnimation = new MovingAnimation(0, 0, 20, true, 4);
	//bulletAnimator = new MovingAnimator();

	AnimatorHolder::animRegister(landingAnimator);
	AnimatorHolder::animRegister(deathAnimator);
	AnimatorHolder::animRegister(takeOffAnimator);
	AnimatorHolder::animRegister(flyAnimator);

	//birds = new std::vector<Bird*>();

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
		/* game loop logic */
		updateGameState();
		/* draw screen */
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
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_LEFT:
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
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				InputManager::shoot(currentGame, currentGame->superAce);
				break;
			case ALLEGRO_KEY_A:
				InputManager::twist();
				break;
			case ALLEGRO_KEY_P:
				pauseGame(currTime);
				//InputManager::pause(gameState);
				break;
			case ALLEGRO_KEY_S:
				InputManager::onKeyS(gameState, display, startButton);
				startNewGame();
				break;
			case ALLEGRO_KEY_L:
				//currentGame->birds->at(0)->flyAnimator->stop();
				//currentGame->birds->at(0)->flyAnimation->setNewOffsets(10, 10);
				//currentGame->birds->at(0)->startMoving();
				break;
			case ALLEGRO_KEY_ENTER:
				if (gameState == GAME_STATE_GAMEOVER) {
					InputManager::onKeyEnter(gameState, display, startButton, gameOverButton);
					cleanGamePlay();
				}
				break;
				/* O:  Just for our debugging*/
			case ALLEGRO_KEY_O:
				if (gameState == GAME_STATE_MAINGAME) {
					gameState = GAME_STATE_GAMEOVER;
					gameOverButton->setVisibility(true);
					gameOverButton->startFlashing();
					break;
				}
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
		if (currentGame->superAce->isSuperAceDead()) {
			gameOver(getCurrTime());
		}

		CollisionChecker::getInstance()->check();
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
		gameOver(timestamp);
	}
}

/* show first window with start screen */
void GamePlay::displayMainScreen(unsigned long now) {
	if (gameState == GAME_STATE_MAINGAME) {
		Terrain::getInstance().drawBackground();

		currentGame->superAce->displayAll();

		for (int i = 0; i < currentGame->birds->size(); i++) {
			currentGame->birds->at(i)->displayAll();
		}
		
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
		Terrain::getInstance().updateBackground();
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
	//cout << "terrainX = "<< Terrain::getInstance().getTerrainX()<<" \n";
	if (Terrain::getInstance().getTerrainX()==100) {
		currentGame->createBird(1000, 400, "bonusBird", flyAnimation, flyAnimator);
		cout << "actionPointTriggered \n";
	}
}

void GamePlay::pauseGame(unsigned long now) {
	//TODO: display message with GAME PAUSED
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
	//TODO: display message to play again
	cout << "GAME OVER FILARAKI";

	gameState = GAME_STATE_GAMEOVER;

	currentGame->highScore = 0;
	currentGame->gameRunning = false;

	Terrain::getInstance().drawBackground();
	//->setVisibility(true);

	//gameOverButton->startFlashing();
	if (gameOverButton->isSpriteVisible()) {
		gameOverButton->display(Rect(0, 0, 0, 0));
	}
	
	al_flip_display();
	al_clear_to_color(al_map_rgb(0, 0, 0));

	Terrain::getInstance().updateBackground();
}

void GamePlay::startNewGame() {
	gameState = GAME_STATE_MAINGAME;
	// TODO: play music ?
	

	currentGame = new GameLogic(takeOffAnimation,
								takeOffAnimator,
								landingAnimation,
								landingAnimator,
								deathAnimation,
								deathAnimator);

	Terrain::cleanUp();
	displayMainScreen(getCurrTime());
	
	// register superAce - birds collisionList
	/*BIRDS* birds = currentGame->birds;
	for (unsigned int i = 0; i < birds->size(); i++) {
		CollisionChecker::getInstance()->
			registerCollisions(currentGame->superAce,
							   currentGame->birds->at(i));

		DROPPINGS* bullshits = currentGame->birds->at(i)->droppings;
		for (unsigned int i = 0; i < bullshits->size(); i++) {
			CollisionChecker::getInstance()->
				registerCollisions(currentGame->superAce,
									currentGame->birds->at(i)->droppings->at(i));
		}
	}*/
}

void GamePlay::cleanGamePlay() {
	// TODO: clean all instances of all the classes!
	//
	if (gameState != GAME_STATE_INTRO) {
		//if (currentGame)
		//	delete currentGame;


		Terrain::cleanUp();
		//BitmapLoader::~BitmapLoader();

		CollisionChecker::getInstance()->cleanUp();
		//AnimationFilmHolder::destroy();

		//cleanAllegro();
	}
}

void GamePlay::cleanAllegro() {
//	al_destroy_timer(lpsTimer);
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