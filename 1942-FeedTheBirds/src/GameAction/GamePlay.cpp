#include <stdio.h>
#include <allegro5/allegro.h>
#include "../../include/GameAction/GamePlay.h"

bool GamePlay::replay = true;

GamePlay::GamePlay() :
	title("1942 - Feed the birds!"),
	windowHeight(800), windowWidth(600) {
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

}

void GamePlay::reset() {

}

void GamePlay::save() {

}

void GamePlay::saveRep() {

}

void GamePlay::load() {

}

void GamePlay::loadRep() {

}