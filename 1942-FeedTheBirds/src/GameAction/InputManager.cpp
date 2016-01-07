#include "../../include/GameAction/InputManager.h"

void InputManager::moveUp() {
	
}

void InputManager::moveDown() {
}

void InputManager::moveLeft() {
}

void InputManager::moveRight() {
}

void InputManager::shoot() {
}

void InputManager::twist() {
}

void InputManager::pause(int &gameState) {
	gameState = GAME_STATE_PAUSED;
}

void InputManager::onKeyS(int &gameState, ALLEGRO_DISPLAY* &display) {
	if (gameState == GAME_STATE_INTRO) {
		// destroy start screen and create a new one with new dimensions
		al_resize_display(display, SCREEN_WINDOW_WIDTH, SCREEN_WINDOW_HEIGHT);
		al_set_new_window_position( 0, 0);
		gameState = GAME_STATE_MAINGAME;
	}
}

void InputManager::onKeyEnter(int &gameState, ALLEGRO_DISPLAY* &display) {
	if (gameState == GAME_STATE_GAMEOVER) {
		al_resize_display(display, START_SCREEN_WINDOW_WIDTH, START_SCREEN_WINDOW_HEIGHT);
		al_set_new_window_position(0, 0);
		gameState = GAME_STATE_INTRO;
	}
}