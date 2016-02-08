#include "..\..\include\Terrain\TerrainStartScreen.h"

TerrainStartScreen::TerrainStartScreen()
{
	bgImage = al_load_bitmap("1942-FeedTheBirds\\data\\Bitmaps\\startscreen\\fallingShit.png");
	stopWarsImage = al_load_bitmap("1942-FeedTheBirds\\data\\Bitmaps\\startscreen\\stopWarsBitmap.png");
	gameInfoImage = al_load_bitmap("1942-FeedTheBirds\\data\\Bitmaps\\startscreen\\gameInfo.png");
	font1 = al_load_ttf_font(font_file, 48, 0);
	font2 = al_load_ttf_font(font_file, -48, 0);
	width = START_SCREEN_WINDOW_WIDTH;
	height = START_SCREEN_WINDOW_HEIGHT;
	velX = 0;
	velY = 3;
	dirX = 1;
	dirY = 1;
}

TerrainStartScreen::~TerrainStartScreen() {
}

TerrainStartScreen& TerrainStartScreen::getInstance() {
	static TerrainStartScreen instance;
	return instance;
}

void TerrainStartScreen::updateBackground() {
	this->y += this->velY * this->dirY;
	if (this->y >= this->height)// <= 0)
		this->y = 0;
}

void TerrainStartScreen::drawBackground() {
	al_draw_bitmap(this->bgImage, this->x, this->y, 0);

	// to achieve scrollable bg
	if (this->y <= this->height )
		al_draw_bitmap(this->bgImage, this->x, this->y-this->height, 0);
	
	al_draw_text(font3, bright_green, 100, 100, ALLEGRO_ALIGN_CENTER, "1942 - ");
	//al_draw_text(font1, bright_green, 310, 90, ALLEGRO_ALIGN_CENTER, "STOP WARS!");

	al_draw_bitmap(stopWarsImage, 140, 20, 0);

	al_draw_text(font3, bright_green, 310, 200, ALLEGRO_ALIGN_CENTER, "CHRISTOULAKIS NIKOS");
	al_draw_text(font3, bright_green, 310, 230, ALLEGRO_ALIGN_CENTER, "PAPADAKI ELENI");
	al_draw_text(font3, bright_green, 310, 260, ALLEGRO_ALIGN_CENTER, "STAYRAKANTONAKI IRINI");

	al_draw_bitmap(gameInfoImage, 167, 280, 0);
}