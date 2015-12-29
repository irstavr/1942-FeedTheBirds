#include <stdio.h>
#include <allegro5/allegro.h>
#include "../../include/GameAction/GamePlay.h"


GamePlay::GamePlay() :
	title("anti1942 - StopWars"),
	windowHeight(1460), windowWidth(669),
	gameState(GAME_STATE_INTRO) 
{
	//time(-1), startTime(0), status(1),
	//musicOn(false), pauseTime(-1.5), colorB(false) {
}

GamePlay *GamePlay::instance(bool newOne) {
	static GamePlay* gamegui = 0;
	if (!gamegui || newOne)
		gamegui = new GamePlay();
	return gamegui;
}

GamePlay::~GamePlay() {

}

bool GamePlay::getSignal() {
	return true;
}

bool GamePlay::FrameFunc() {
	return true;
}

bool GamePlay::RenderFunc()
{
	return true;
}

void GamePlay::start() {
	gamePlayInit();
}

void GamePlay::gamePlayInit() {
	// test for failure
	if (0 != al_init()) { 
		fprintf(stderr, "%s", al_error); 
		exit(1); 
	}
	al_install_keyboard();
}

void GamePlay::reset() {
	//TODO next version
}

void GamePlay::save() {
	//TODO next version
}

void GamePlay::saveRep() {
	//TODO next version
}

void GamePlay::load() {
	//TODO next version
}

void GamePlay::loadRep() {
	//TODO next version
}