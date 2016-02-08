/*
* 1942 - STOP WARS! version
* Created for HY454 course at CSD UoC, Winter Semester 2015
* 
* main.cpp
*
*  Created on: 
*      Author: Christoulakis Nikos
*      Author: Papadaki Eleni	
*      Author: Stavrakantonaki Irini
*/

// for our use only 
// to find memory leaks using the CRT library
#define _CRTDBG_MAP_ALLOC
#include <windows.h>
#include "Stackwalker.h"

#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>
#include <cstdlib>
#include "..\include\GameAction\GamePlay.h"
#include "..\include\Utilities\Utilities.h"

void main()
{
	//just for us to use the memory leaks tester
	InitAllocCheck();

	// block that makes sure that the deconstructors are called
	// before the 
	{
		cerr << "Game Started\n";
		GamePlay *game = GamePlay::instance();
		while (game->gameState != GAME_STATE_FINISHED) {
			game->start();
		}
		delete game;
	}

	_CrtDumpMemoryLeaks();
	DeInitAllocCheck();
}