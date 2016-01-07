#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "allegro5\allegro.h"
#include "..\GameAction\GamePlay.h"

namespace InputManager {

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	/* called if press space bar */
	void shoot();
	/* called if press key A */
	void twist();
	/* called if press P */
	void pause(int&);

	void onKeyEnter(int&,ALLEGRO_DISPLAY*&);
	void onKeyS(int&, ALLEGRO_DISPLAY*&);
}

#endif