﻿#include "..\..\include\Terrain\Terrain.h"

using namespace std;

Terrain::Terrain() :
	font_file("1942-FeedTheBirds\\data\\Fonts\\fat.ttf"),
	width(SCREEN_WINDOW_WIDTH),
	height(SCREEN_WINDOW_WIDTH),
	x(0), y(0), velX(1), velY(0), dirX(-1), dirY(1), numOfScrolls(0)
{
	bgImage = al_load_bitmap("1942-FeedTheBirds\\data\\Bitmaps\\terrain\\background5.png");
	remainingLivesImage = al_load_bitmap("1942-FeedTheBirds\\data\\Bitmaps\\life.png");
	remainingLoopsImage = al_load_bitmap("1942-FeedTheBirds\\data\\Bitmaps\\loop.png");
	scoreImage = al_load_bitmap("1942-FeedTheBirds\\data\\Bitmaps\\terrain\\ScoreBitmap.png");
	highScoreImage = al_load_bitmap("1942-FeedTheBirds\\data\\Bitmaps\\terrain\\HighScoreBitmap.png");

	font1 = al_load_ttf_font(font_file, 28, 0);
	font2 = al_load_ttf_font(font_file, -28, 0);
	font3 = al_load_ttf_font(font_file, 16, 0);

	font4 = al_load_ttf_font(font_file, 12, 0);
	if (!font1 || !font2) {
		al_show_native_message_box(NULL, "Error", NULL, "failed to load font file!\n", NULL, NULL);
		return;
	}
	bright_green = al_map_rgba_f(0.8, 0.0, 0.0, 1.0);
	black = al_map_rgba_f(0, 0, 0, 1.0);
}

Terrain::~Terrain() {
}

float Terrain::getTerrainX() {
	return this->x;
}

void Terrain::updateBackground() {
	this->x += this->velX * this->dirX;
}

void Terrain::drawBackground(int score, int highscore, int lives, int loops) {
	
	al_draw_bitmap(this->bgImage, this->x, this->y, 0);
	if (this->x + this->width < SCREEN_WINDOW_WIDTH) {
		al_draw_bitmap(this->bgImage, this->x + this->width, this->y, 0);
	}

	al_draw_text(font2, bright_green, 100, 10, ALLEGRO_ALIGN_CENTER, to_string(score).c_str());
	al_draw_text(font1, bright_green, 1200, 10, ALLEGRO_ALIGN_CENTER, to_string(highscore).c_str());

	int i;
	for (i = 0; i < lives; i++) {
		al_draw_bitmap(remainingLivesImage, 20 + (i * 81), 610, 0);
	}

	int loopsImgWidth = al_get_bitmap_width(remainingLoopsImage);
	for (i = 0; i < loops; i++) {
		al_draw_scaled_bitmap(remainingLoopsImage, 0, 0, loopsImgWidth, loopsImgWidth, 1220-(i*55), 600, 50, 50, 0);
	}
}