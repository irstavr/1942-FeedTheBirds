
#include "..\..\include\Terrain\Terrain.h"

Terrain::Terrain() {
	bgImage = al_load_bitmap("1942-FeedTheBirds\\data\\Bitmaps\\terrain\\sample_terrain.bmp");

	font_file = "1942-FeedTheBirds\\data\\Fonts\\karmatic_arcade_font.ttf";
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

void Terrain::create(float x, float y, float velx, float vely, int width, int height, int dirX, int dirY)
{
	this->x = x;
	this->y = y;
	this->velX = velx;
	this->velY = vely;
	this->width = width;
	this->height = height;
	this->dirX = dirX;
	this->dirY = dirY;
}

void Terrain::updateBackground()
{
	this->y += this->velY * this->dirY;
	if (this->y + this->height <= 0)
		this->y = 0;
}

void Terrain::drawBackground(float SCREEN_WINDOW_HEIGHT)
{
	al_draw_bitmap(this->bgImage, this->x, this->y, 0);

	if (this->y + this->height < SCREEN_WINDOW_HEIGHT)
		al_draw_bitmap(this->bgImage, this->x, this->y + this->height, 0);

	al_flip_display();
	al_clear_to_color(al_map_rgb(0, 0, 0));
}
