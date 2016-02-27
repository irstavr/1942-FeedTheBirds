/*
* 1942 - STOP WARS! version
* 
* main.cpp
*
*  Created on: 
*      Author: Christoulakis Nikos
*      Author: Papadaki Eleni	
*      Author: Stavrakantonaki Irini
*/

#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>
#include <cstdlib>
#include "..\include\GameAction\GamePlay.h"
#include "..\include\Utilities\Utilities.h"

void main()
{
	// block that makes sure that the deconstructors are called before 
	{
		cerr << "Game Started\n";
		GamePlay *game = GamePlay::instance();
		while (game->gameState != GAME_STATE_FINISHED) {
			game->start();
		}
		delete game;
	}
}