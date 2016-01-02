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
	bgImage = al_load_bitmap("starBG.png");
	mgImage = al_load_bitmap("starMG.png");
	fgImage = al_load_bitmap("starFG.png");
}

void TerrainStartScreen::drawBackground(ALLEGRO_BITMAP *dest) {
	//al_blit(bgImage, dest, offsetBg, 0, 0, 0, bgImage->w - offsetBg, bgImage->h);
	//for (int x = bgImage->w - offsetBg; x < SCREEN_WINDOW_WIDTH; x += bgImage->w) {
	//	al_blit(bgImage, dest, 0, 0, x, 0, bgImage->w, bgImage->h);
	//}
}

void TerrainStartScreen::scrollBackground() {
	offsetBg += PIXEL_SCROLL_PER_CYCLE;
}


void TerrainStartScreen::initBackground(TerrainStartScreen back, float x, float y, float velx, float vely, int width, int height, int dirX, int dirY, ALLEGRO_BITMAP *image)
{
	back.x = x;
	back.y = y;
	back.velX = velx;
	back.velY = vely;
	back.width = width;
	back.height = height;
	back.dirX = dirX;
	back.dirY = dirY;
	back.image = image;
}

void TerrainStartScreen::updateBackground(TerrainStartScreen back)
{
	back.x += back.velX * back.dirX;
	if (back.x + back.width <= 0)
		back.x = 0;
}

void TerrainStartScreen::drawBackground(TerrainStartScreen back)
{
	al_draw_bitmap(back.image, back.x, back.y, 0);

	if (back.x + back.width < SCREEN_WINDOW_WIDTH)
		al_draw_bitmap(back.image, back.x + back.width, back.y, 0);
}