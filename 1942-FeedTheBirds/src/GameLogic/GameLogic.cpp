#include "..\..\include\GameLogic\GameLogic.h"

GameLogic::GameLogic (SuperAce  *superAce, BIRDS &birds, int height, int width) :
	superAce(superAce), birds(birds),
	height(height), width(width),
	gameRunning(true) {
}

bool GameLogic::isRunning() const {
	return gameRunning;
}
