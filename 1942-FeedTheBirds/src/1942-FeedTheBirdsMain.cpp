/*
*  main.cpp
*
*  Created on: 
*      Author: 
*      Author: 
*      Author: 
*/
#include <stdio.h>
#include "../include/GameAction/GamePlay.h"
#include <cstdlib>

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
