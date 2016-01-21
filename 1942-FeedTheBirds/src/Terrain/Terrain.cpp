#include "..\..\include\Terrain\Terrain.h"

Terrain* Terrain::terrain;

Terrain::Terrain() :
	font_file("1942-FeedTheBirds\\data\\Fonts\\karmatic_arcade_font.ttf"),
	width(TERRAIN_IMAGE_WIDTH),
	height(TERRAIN_IMAGE_HEIGHT),
	x(0), y(0), velX(3), velY(0), dirX(-1), dirY(1)
{
	bgImage = al_load_bitmap("1942-FeedTheBirds\\data\\Bitmaps\\terrain\\sample_terrain.bmp");
	remainingLivesImage = al_load_bitmap("1942-FeedTheBirds\\data\\Bitmaps\\life.png");
	remainingLoopsImage = al_load_bitmap("1942-FeedTheBirds\\data\\Bitmaps\\life.png");

	font1 = al_load_ttf_font(font_file, 28, 0);
	font2 = al_load_ttf_font(font_file, -28, 0);
	if (!font1 || !font2) {
		al_show_native_message_box(NULL, "Error", NULL, "failed to load font file!\n", NULL, NULL);
		return;
	}
	bright_green = al_map_rgba_f(0.5, 1.0, 0.5, 1.0);
	grey = al_map_rgba_f(0.7, 0.7, 0.7, 1.0);
}

Terrain::~Terrain() {
}

void Terrain::cleanUp() {
	delete terrain;
}

Terrain& Terrain::getInstance() {
	static Terrain instance;
	return instance;
}

float Terrain::getTerrainX() {
	return this->x;
}

void Terrain::updateBackground() {
	this->x += this->velX * this->dirX;
	if (this->x + this->width <= 0)
		this->x = 0;
}

void Terrain::drawBackground() {

	//if (this->x + this->width < SCREEN_WINDOW_WIDTH)
		al_draw_scaled_bitmap(bgImage, 0, 0, width, height, x, y, width * 3, height * 3, 0);
		//al_draw_bitmap(this->bgImage, this->x + this->width, this->y, 0);

		al_draw_text(font2, bright_green, 100, 10, ALLEGRO_ALIGN_CENTER, "Score ");
		al_draw_text(font2, bright_green, 220, 10, ALLEGRO_ALIGN_CENTER, "3000 ");
		al_draw_text(font1, bright_green, 510, 10, ALLEGRO_ALIGN_CENTER, "High Score ");
		al_draw_text(font1, bright_green, 700, 10, ALLEGRO_ALIGN_CENTER, "10000 ");

		//while (lives != 0) {
		al_draw_scaled_bitmap(remainingLivesImage, 0, 0, 170, 170, 20, 600, 70, 70, 0);
			//al_draw_bitmap(remainingLivesImage, 100, 600, 0);
		//}
		//while (lives != 0) {
		al_draw_scaled_bitmap(remainingLivesImage, 0, 0, 170, 170, 1200, 600, 70, 70, 0);
		//}

}