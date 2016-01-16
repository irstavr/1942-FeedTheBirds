#include "../../include/GameAction/InputManager.h"

void InputManager::moveUp(SuperAce* &superAce) {
	superAce->moveUp();
}

void InputManager::moveDown(SuperAce* &superAce) {
	superAce->moveDown();
}

void InputManager::moveLeft(SuperAce* &superAce) {
	superAce->moveLeft();
}

void InputManager::moveRight(SuperAce* &superAce) {
	superAce->moveRight();
}


void InputManager::move(bool up, bool down, bool left, bool right, SuperAce* &superAce) {

	//cout << "up=" << up << " down=" << down<< " left=" << left<< " right= " << right << "\n";
	if (up) {
		moveUp(superAce);
	}
	if (down) {
		moveDown(superAce);
	}
	if (left) {
		moveLeft(superAce);
	}
	if (right) {
		moveRight(superAce);
	}
}

void InputManager::shoot(Fish* &fish) {
	/*MovingAnimation *bulletAnimation = new MovingAnimation(0, 0, 20, true, 4);
	MovingAnimator *bulletAnimator = new MovingAnimator();

	AnimatorHolder::animRegister(bulletAnimator);

	fish = new Fish(230, 300,
		(AnimationFilm*)
		AnimationFilmHolder::getSingleton()->
		getFilm("doubleFish"),
		bulletAnimation,
		bulletAnimator
		);*/
}

void InputManager::twist() {
}

void InputManager::pause(int &gameState) {
	if(gameState == GAME_STATE_MAINGAME) gameState = GAME_STATE_PAUSED;
}

void InputManager::onKeyS(int &gameState, ALLEGRO_DISPLAY* &display, Button* &startButton) {
	if (gameState == GAME_STATE_INTRO) {
		// destroy start screen and create a new one with new dimensions
		al_resize_display(display, SCREEN_WINDOW_WIDTH, SCREEN_WINDOW_HEIGHT);
		al_set_new_window_position( 0, 0);
	
		startButton->stopFlashing();
		startButton->setVisibility(false);
		gameState = GAME_STATE_MAINGAME;
	}
}

void InputManager::onKeyEnter(int &gameState, ALLEGRO_DISPLAY* &display, Button* &startButton) {
	if (gameState == GAME_STATE_GAMEOVER) {
		al_resize_display(display, START_SCREEN_WINDOW_WIDTH, START_SCREEN_WINDOW_HEIGHT);
		al_set_new_window_position(0, 0);
		gameState = GAME_STATE_INTRO;

		startButton->startFlashing();
		startButton->setVisibility(true);
	}
}