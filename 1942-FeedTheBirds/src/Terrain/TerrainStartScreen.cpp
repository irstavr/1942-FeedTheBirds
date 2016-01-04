#include "..\..\include\Terrain\TerrainStartScreen.h"

TerrainStartScreen::TerrainStartScreen() {
}

TerrainStartScreen::~TerrainStartScreen() {

}

TerrainStartScreen& TerrainStartScreen::getInstance() {
	static TerrainStartScreen instance;
	return instance;
}

void TerrainStartScreen::create() {
	//bgImage = al_load_bitmap("starBG.png");
	//mgImage = al_load_bitmap("starMG.png");
	//fgImage = al_load_bitmap("starFG.png");
}

//void TerrainStartScreen::drawBackground(ALLEGRO_BITMAP *dest) {
	//al_blit(bgImage, dest, offsetBg, 0, 0, 0, bgImage->w - offsetBg, bgImage->h);
	//for (int x = bgImage->w - offsetBg; x < SCREEN_WINDOW_WIDTH; x += bgImage->w) {
	//	al_blit(bgImage, dest, 0, 0, x, 0, bgImage->w, bgImage->h);
	//}
//}

void TerrainStartScreen::scrollBackground() {
	offsetBg += PIXEL_SCROLL_PER_CYCLE;
}

