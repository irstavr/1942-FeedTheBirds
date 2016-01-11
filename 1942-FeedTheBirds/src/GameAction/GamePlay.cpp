#include "..\..\include\GameAction\GamePlay.h"

GamePlay::GamePlay() :
	title("anti1942 - StopWars"),
	gameState(GAME_STATE_INTRO),
	windowHeight(START_SCREEN_WINDOW_HEIGHT), windowWidth(START_SCREEN_WINDOW_WIDTH)
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
	Terrain::getInstance();
	TerrainStartScreen::getInstance();
	AnimationFilmHolder::initialize("1942-FeedTheBirds\\data\\films.ini");
	AnimationFilmHolder *animFH = AnimationFilmHolder::getSingleton();

	CollisionChecker::getInstance()->initialize();

	// Add start game button
	FlashingAnimation *flashAnimation = new FlashingAnimation(1, 250, 600, 0);
	FlashingAnimator *flashAnimator = new FlashingAnimator();
	startButton = new Button(0, 
							 0, 
							(AnimationFilm *) 
								AnimationFilmHolder::getSingleton()->
								getFilm("StartButton"),
							flashAnimation,
							flashAnimator);
	AnimatorHolder::animRegister(flashAnimator);

}

void GamePlay::runMainLoop() {
	/* finish == exit of game */
	while (gameState != GAME_STATE_FINISHED) {
		currTime = getCurrTime();
		al_wait_for_event(eventQueue, &alEvent);

		/* draw screen */
		render(currTime);
		/* read from local input event queue */
		inputManagement(alEvent);
		/* game loop logic */
		updateGameState();
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
			if (alEvent.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
				gameState = GAME_STATE_FINISHED;
				break;
			}
		case ALLEGRO_EVENT_KEY_DOWN:
			switch (alEvent.keyboard.keycode) {
				case ALLEGRO_KEY_UP:
					InputManager::moveUp();
					break;
				case ALLEGRO_KEY_DOWN:
					InputManager::moveDown();
					break;
				case ALLEGRO_KEY_RIGHT:
					InputManager::moveRight();
					break;
				case ALLEGRO_KEY_LEFT:
					InputManager::moveLeft();
					break;
				case ALLEGRO_KEY_SPACE:
					InputManager::shoot();
					break;
				case ALLEGRO_KEY_A:
					InputManager::twist();
					break;
				case ALLEGRO_KEY_P:
					InputManager::pause(gameState);
					break;
				case ALLEGRO_KEY_S:
					InputManager::onKeyS(gameState, display);
					break;
				case ALLEGRO_KEY_ENTER:
					InputManager::onKeyEnter(gameState, display);
					break;
				/* O:  Just for our debugging*/
				case ALLEGRO_KEY_O:
					if (gameState == GAME_STATE_MAINGAME) {
						gameState = GAME_STATE_GAMEOVER;
						break;
					}
			}
		}	
	} 
	if (gameState == GAME_STATE_PAUSED && alEvent.keyboard.keycode == ALLEGRO_KEY_R) {
		gameState = GAME_STATE_MAINGAME;
	}

}

/* game loop logic */
void GamePlay::updateGameState() {
	if (gameState == GAME_STATE_MAINGAME) {
		// TODO
		// initialize:
		// AI
		// Animation progress
		// check if win
		// update scores/lives/etc on the display
		// etc 

		CollisionChecker::getInstance()->check();
	}
}

void GamePlay::render(unsigned long timestamp)
{
	if (!al_is_event_queue_empty(eventQueue))
		return;

	//al_clear_to_color(al_map_rgba(0, 0, 0, 0));
		
	if (gameState == GAME_STATE_INTRO) {
		displayStartScreen(timestamp);
	}

	if (gameState == GAME_STATE_MAINGAME) {
		displayMainScreen(timestamp);
	}

	if (gameState == GAME_STATE_PAUSED) {
		//TODO: display message with GAME PAUSED
	}

	if (gameState == GAME_STATE_GAMEOVER) {
		//TODO: display message with GAME OVER
	}

	//al_flip_display();
}

/* show first window with start screen */
void GamePlay::displayMainScreen(unsigned long now) {
	if (gameState == GAME_STATE_MAINGAME) {
		Terrain::getInstance().drawBackground();
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
		Terrain::getInstance().updateBackground();
	}
}

/* show first window with start screen */
void GamePlay::displayStartScreen(unsigned long now) {		
	TerrainStartScreen::getInstance().drawBackground();
	al_flip_display();
	al_clear_to_color(al_map_rgb(0, 0, 0));
	TerrainStartScreen::getInstance().updateBackground();
}

void GamePlay::gameStarting() {
	gameState = GAME_STATE_MAINGAME;
	// TODO: play music ?
}

void GamePlay::cleanGamePlay() {
	cleanAllegro();
	// TODO: clean all instances of all the classes!
	//
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