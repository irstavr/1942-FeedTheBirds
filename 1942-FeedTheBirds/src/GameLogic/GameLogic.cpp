#include "..\..\include\GameLogic\GameLogic.h"

GameLogic::GameLogic (SuperAce  *superAce, BIRDS &birds, 
						int height, int width) :
		superAce(superAce), birds(birds),
		height(height), width(width),
		gameRunning(true) {
	profile = new PlayerProfile(std::make_pair(5,5));
}

bool GameLogic::isRunning() const {
	return gameRunning;
}

void GameLogic::clearUp() {
	//profile->~PlayerProfile();
	//superAce->die();
	//birds->
}