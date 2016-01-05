#include "..\..\include\Terrain\TerrainStartScreen.h"

TerrainStartScreen::TerrainStartScreen() {
}

TerrainStartScreen::~TerrainStartScreen() {

}

TerrainStartScreen& TerrainStartScreen::getInstance() {
	static TerrainStartScreen instance;
	return instance;
}

void TerrainStartScreen::create(ALLEGRO_BITMAP *image, float x, float y, float velx, float vely, int width, int height, int dirX, int dirY)
{
	//bgImage = al_load_bitmap("starBG.png");
	//mgImage = al_load_bitmap("starMG.png");
	//fgImage = al_load_bitmap("starFG.png");

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
	this->y += this->velY * this->dirY;
	if (this->y + this->height <= 0)
		this->y = 0;
}

void TerrainStartScreen::drawBackground(ALLEGRO_BITMAP *image)
{
	al_draw_bitmap(this->image, this->x, this->y, 0);

	if (this->y + this->height < SCREEN_WINDOW_HEIGHT)
		al_draw_bitmap(this->image, this->x , this->y + this->height, 0);
}

