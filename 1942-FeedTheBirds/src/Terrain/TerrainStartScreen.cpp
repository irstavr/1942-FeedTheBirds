#include "..\..\include\Terrain\TerrainStartScreen.h"

TerrainStartScreen::TerrainStartScreen()
{
	bgImage = al_load_bitmap("1942-FeedTheBirds\\data\\Bitmaps\\terrain\\forest.png");
	stopWarsImage = al_load_bitmap("1942-FeedTheBirds\\data\\Bitmaps\\startscreen\\stopWarsImage.png");
	font1 = al_load_ttf_font(font_file, 48, 0);
	font2 = al_load_ttf_font(font_file, -48, 0);
	font3 = al_load_ttf_font(font_file, 20, 0);
	width = START_SCREEN_WINDOW_WIDTH;
	height = START_SCREEN_WINDOW_HEIGHT;
	velX = 0;
	velY = 3;
	dirX = 1;
	dirY = -1;
}

TerrainStartScreen::~TerrainStartScreen() {
}

TerrainStartScreen& TerrainStartScreen::getInstance() {
	static TerrainStartScreen instance;
	return instance;
}

void TerrainStartScreen::updateBackground() {
	this->y += this->velY * this->dirY;
	if (this->y + this->height <= 0)
		this->y = 0;
}

void TerrainStartScreen::drawBackground() {
	al_draw_bitmap(this->bgImage, this->x, this->y, 0);

	if (this->y + this->height < START_SCREEN_WINDOW_HEIGHT)
		al_draw_bitmap(this->bgImage, this->x, this->y + this->height, 0);
	
	al_draw_text(font2, bright_green, 310, 20, ALLEGRO_ALIGN_CENTER, "1942");
	al_draw_text(font1, bright_green, 310, 90, ALLEGRO_ALIGN_CENTER, "STOP WARS!");

	al_draw_bitmap(stopWarsImage, 210, 150, 0);

	al_draw_text(font3, grey, 310, 310, ALLEGRO_ALIGN_CENTER, "Irini");
	al_draw_text(font3, grey, 310, 340, ALLEGRO_ALIGN_CENTER, "Eleni");
	al_draw_text(font3, grey, 310, 370, ALLEGRO_ALIGN_CENTER, "Nikos");
}