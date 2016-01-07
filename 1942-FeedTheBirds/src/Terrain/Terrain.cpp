
#include "..\..\include\Terrain\Terrain.h"

Terrain::Terrain() :
	font_file("1942-FeedTheBirds\\data\\Fonts\\karmatic_arcade_font.ttf"),
	width(SCREEN_WINDOW_WIDTH),
	height(SCREEN_WINDOW_HEIGHT),
	x(0), y(0), velX(0), velY(3), dirX(1), dirY(-1)
{
	bgImage = al_load_bitmap("1942-FeedTheBirds\\data\\Bitmaps\\terrain\\sample_terrain.bmp");

	font1 = al_load_ttf_font(font_file, 48, 0);
	font2 = al_load_ttf_font(font_file, -48, 0);
	if (!font1 || !font2) {
		al_show_native_message_box(NULL, "Error", NULL, "failed to load font file!\n", NULL, NULL);
		return;
	}
	bright_green = al_map_rgba_f(0.5, 1.0, 0.5, 1.0);
}

Terrain::~Terrain() {
}

Terrain& Terrain::getInstance() {
	static Terrain instance;
	return instance;
}

void Terrain::updateBackground() {
	this->x += this->velX * this->dirX;
	if (this->x + this->width <= 0)
		this->x = 0;
}

void Terrain::drawBackground() {
	al_draw_scaled_bitmap(bgImage, 0, 0, width, height, x, y, width * 3, height * 3, 0);

	if (this->x + this->width < SCREEN_WINDOW_WIDTH)
		al_draw_bitmap(this->bgImage, this->x + this->width, this->y, 0);
}


