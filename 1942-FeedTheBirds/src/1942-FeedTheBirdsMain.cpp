/*
*  main.cpp
*
*  Created on: 
*      Author: 
*      Author: 
*      Author: 
*/
#include <stdio.h>
#include <cstdlib>
#include "..\include\GameAction\GamePlay.h"
#include "..\include\Utilities\Utilities.h"

int main()
{
	GamePlay *game = GamePlay::instance();
	while (game->gameState != GAME_STATE_FINISHED) {
		game->start();
		//delete game;
		//game = GamePlay::instance(true);
	}
	return 0;
}
