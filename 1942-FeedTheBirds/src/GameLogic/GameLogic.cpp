#include "..\..\include\GameLogic\GameLogic.h"

GameLogic::GameLogic (SuperAce  *superAce, BIRDS &birds, FISHES &fishes, int height, int width) :
	superAce(superAce), birds(birds), fishes(fishes),
	height(height), width(width),
	gameRunning(true) {
}

bool GameLogic::isRunning() const {
	return gameRunning;
}

void GameLogic::clearUp() {
	profile->~PlayerProfile();
	superAce->die();
	//birds->
}