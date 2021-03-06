#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "allegro5\allegro.h"
#include "..\GameAction\GamePlay.h"
#include "..\Objects\Items\Button.h"
#include "..\Objects\Characters\SuperAce.h"
#include "..\Objects\Items\Fish.h"

namespace InputManager {

	void moveUp(SuperAce* &superAce);
	void moveDown(SuperAce* &superAce);
	void moveLeft(SuperAce* &superAce);
	void moveRight(SuperAce* &superAce);


	void move(bool, bool, bool, bool, SuperAce* &superAce);

	/* called if press space bar */
	void shoot(GameLogic* &game, SuperAce* &superAce);
	/* called if press key A */
	void twist(SuperAce *& superAce);
	/* called if press P */
	void pause(int&);

	void onKeyEnter(int&, ALLEGRO_DISPLAY*&, Button* &startButton, Button* &gameOverButton, Button* &winButton);
	void onKeyS(int &gameState, ALLEGRO_DISPLAY* &display, Button* &startButton);
}

#endif