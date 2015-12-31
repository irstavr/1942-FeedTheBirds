#include "../../include/GameAction/GamePlay.h"

GamePlay::GamePlay() :
	title("anti1942 - StopWars"),
	windowHeight(SCREEN_WINDOW_HEIGHT), windowWidth(SCREEN_WINDOW_WIDTH),
	gameState(GAME_STATE_INTRO) 
{
	//time(-1), startTime(0), status(1),
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

bool GamePlay::getSignal() {
	return true;
}

bool GamePlay::FrameFunc() {
	return true;
}

bool GamePlay::RenderFunc()
{
	return true;
}

void GamePlay::start() {
	gamePlayInit();
}

void GamePlay::gamePlayInit() {
	
	if (!initAllegro()) {
		return;
	}
	// Main loop 
	runMainLoop();
	// Cleaning
	cleanAllegro();
}

void GamePlay::runMainLoop() {
	/*
	1. init game engine
	2. input handling
	3. game play
	4. check if game ends

	while (running) {
		processInput();
		updateGameState();
		drawScreen();
	}
	*/

	float pos_x = SCREEN_WINDOW_WIDTH / 2;
	float pos_y = SCREEN_WINDOW_HEIGHT / 2;
	while (gameState == GAME_STATE_INTRO) {
		al_wait_for_event(eventQueue, &alEvent);
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
			switch (alEvent.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				pos_y -= 10;
				break;
			case ALLEGRO_KEY_DOWN:
				pos_y += 10;
				break;
			case ALLEGRO_KEY_RIGHT:
				pos_x += 10;
				break;
			case ALLEGRO_KEY_LEFT:
				pos_x -= 10;
				break;
			}
		case ALLEGRO_EVENT_TIMER:
			if (alEvent.timer.source == lpsTimer) {
				fprintf(stderr, "Logic updated\n");
			}
			else if (alEvent.timer.source == fpsTimer) {
				al_draw_filled_rectangle(pos_x, pos_y, pos_x + 30, pos_y + 30, al_map_rgb(255, 0, 255));
				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
				//fprintf(stdout, "Display updated\n");
			}
			break;
		}
		fprintf(stderr, "Limitless update\n");
	}
}


void GamePlay::cleanAllegro() {
	al_destroy_timer(lpsTimer);
	al_destroy_timer(fpsTimer);
	al_destroy_display(display);
	al_destroy_event_queue(eventQueue);
}

bool GamePlay::initAllegro() {
	
	// test for failure
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

	display = al_create_display(SCREEN_WINDOW_WIDTH, SCREEN_WINDOW_HEIGHT);
	if (!display) {
		al_show_native_message_box(NULL, "Error", NULL, "failed to create display!\n", NULL, NULL);
		al_destroy_timer(fpsTimer);
		al_destroy_timer(lpsTimer);
		return false;
	}
	al_set_window_position(display, 0, 0);

	eventQueue = al_create_event_queue();
	if (!eventQueue) {
		al_show_native_message_box(NULL, "Error", NULL, "failed to create event_queue!\n", NULL, NULL);
		al_destroy_display(display);
		al_destroy_timer(fpsTimer);
		al_destroy_timer(lpsTimer);
		return false;
	}

	al_init_font_addon();
	al_init_ttf_addon();
	font1 = al_load_ttf_font("karmatic_arcade_font.ttf", 48, 0);
	font2 = al_load_ttf_font("karmatic_arcade_font.ttf", -48, 0);
	if (!font1 || !font2) {
		al_show_native_message_box(NULL, "Error", NULL, "failed to load font file!\n", NULL, NULL);
		return false;
	}

	bright_green = al_map_rgba_f(0.5, 1.0, 0.5, 1.0);

	al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);

	if (!al_init_primitives_addon()) {
		al_show_native_message_box(NULL, "Error", NULL, "failed to initialize primitives addon!\n", NULL, NULL);
		al_destroy_display(display);
		al_destroy_timer(fpsTimer);
		al_destroy_timer(lpsTimer);
		return false;
	}

	//Tie events to queue
	al_register_event_source(eventQueue, al_get_display_event_source(display));
	al_register_event_source(eventQueue, al_get_keyboard_event_source());
	al_register_event_source(eventQueue, al_get_timer_event_source(fpsTimer));
	al_register_event_source(eventQueue, al_get_timer_event_source(lpsTimer));

	al_clear_to_color(al_map_rgb(0,0,0));

	al_draw_text(font1, bright_green, 10, 10, ALLEGRO_ALIGN_LEFT, "Allegro 5 Rocks!");
	al_draw_text(font2, bright_green, 10, 60, ALLEGRO_ALIGN_LEFT, "Allegro 5 Rocks!");
	al_flip_display();

	//Start timers 
	al_start_timer(lpsTimer); 
	al_start_timer(fpsTimer);
	
	return true;
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