#include "..\..\include\Terrain\TerrainStartScreen.h"

TerrainStartScreen::TerrainStartScreen() {
	bgImage = al_load_bitmap("1942-FeedTheBirds\\data\\Bitmaps\\terrain\\forest.png");
	stopWarsImage = al_load_bitmap("1942-FeedTheBirds\\data\\Bitmaps\\startscreen\\stopWarsImage.png");
}

TerrainStartScreen::~TerrainStartScreen() {

}


void TerrainStartScreen::drawBackground(float SCREEN_WINDOW_HEIGHT)
{
	al_draw_bitmap(this->bgImage, this->x, this->y, 0);

	if (this->y + this->height < SCREEN_WINDOW_HEIGHT)
		al_draw_bitmap(this->bgImage, this->x, this->y + this->height, 0);

	al_draw_text(font1, bright_green, 310, 90, ALLEGRO_ALIGN_CENTER, "STOP WARS!");
	al_draw_text(font2, bright_green, 310, 20, ALLEGRO_ALIGN_CENTER, "1942");

	al_draw_bitmap(stopWarsImage, 180, 150, 0);
	
	al_flip_display();
	al_clear_to_color(al_map_rgb(0, 0, 0));
}


TerrainStartScreen& TerrainStartScreen::getInstance() {
	static TerrainStartScreen instance;
	return instance;
}
