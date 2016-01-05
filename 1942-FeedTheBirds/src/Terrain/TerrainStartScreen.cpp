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

void TerrainStartScreen::initBackground(ALLEGRO_BITMAP *image, float x, float y, float velx, float vely, int width, int height, int dirX, int dirY)
{
	this->x = x;
	this->y = y;
	this->velX = velx;
	this->velY = vely;
	this->width = width;
	this->height = height;
	this->dirX = dirX;
	this->dirY = dirY;
	this->image = image;
}

void TerrainStartScreen::updateBackground(ALLEGRO_BITMAP *image)
{
	this->x += this->velX * this->dirX;
	if (this->x + this->width <= 0)
		this->x = 0;
}

void TerrainStartScreen::drawBackground(ALLEGRO_BITMAP *image)
{
	al_draw_bitmap(this->image, this->x, this->y, 0);

	if (this->x + this->width < SCREEN_WINDOW_WIDTH)
		al_draw_bitmap(this->image, this->x + this->width, this->y, 0);
}

