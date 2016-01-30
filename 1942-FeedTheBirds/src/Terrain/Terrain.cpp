#include "..\..\include\Terrain\Terrain.h"

using namespace std;

Terrain::Terrain() :
	font_file("1942-FeedTheBirds\\data\\Fonts\\karmatic_arcade_font.ttf"),
	width(TERRAIN_IMAGE_WIDTH),
	height(TERRAIN_IMAGE_HEIGHT),
	x(0), y(0), velX(3), velY(0), dirX(-1), dirY(1)
{
	bgImage = al_load_bitmap("1942-FeedTheBirds\\data\\Bitmaps\\terrain\\sample_terrain.bmp");
	remainingLivesImage = al_load_bitmap("1942-FeedTheBirds\\data\\Bitmaps\\life.png");
	remainingLoopsImage = al_load_bitmap("1942-FeedTheBirds\\data\\Bitmaps\\loop.png");

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

float Terrain::getTerrainX() {
	return -((this->x)/3);
}

void Terrain::updateBackground() {
	this->x += this->velX * this->dirX;
	if (this->x + this->width <= 0)
		this->x = 0;
}

void Terrain::drawBackground(int score, int highscore, int lives, int loops) {
	al_draw_scaled_bitmap(bgImage, 0, 0, width, height, x, y, width * 3, height * 3, 0);

	al_draw_text(font2, bright_green, 100, 10, ALLEGRO_ALIGN_CENTER, "Score ");
	al_draw_text(font2, bright_green, 220, 10, ALLEGRO_ALIGN_CENTER, to_string(score).c_str());
	al_draw_text(font1, bright_green, 510, 10, ALLEGRO_ALIGN_CENTER, "High Score ");
	al_draw_text(font1, bright_green, 700, 10, ALLEGRO_ALIGN_CENTER, to_string(highscore).c_str());

	int livesImgWidth = al_get_bitmap_width(remainingLivesImage);

	for (int i = 0; i < lives; i++) {
		al_draw_scaled_bitmap(remainingLivesImage, 0, 0, livesImgWidth, livesImgWidth, 20+(i*61), 600, 60, 60, 0);
	}

	// TODO: change PHOTO for loops
	int loopsImgWidth = al_get_bitmap_width(remainingLoopsImage);

	for (int j = 0; j < loops; j++) {
		al_draw_scaled_bitmap(remainingLoopsImage, 0, 0, loopsImgWidth, loopsImgWidth, 1220-(j*55), 600, 50, 50, 0);
	}
}