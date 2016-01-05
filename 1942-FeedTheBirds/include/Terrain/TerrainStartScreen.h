#ifndef _TERRAIN_START_SCREEN_H_
#define _TERRAIN_START_SCREEN_H_

#include <assert.h>
#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h> 
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include "..\..\include\GameAction\GamePlay.h"

#define PIXEL_SCROLL_PER_CYCLE 5


class TerrainStartScreen {

public:

	static TerrainStartScreen& getInstance();

	void displayTerrain(ALLEGRO_BITMAP *, unsigned long) {}

	void create(ALLEGRO_BITMAP* back, float x, float y, float velx, float vely, int width, int height, int dirX, int dirY);
	void updateBackground(ALLEGRO_BITMAP* back);
	void drawBackground(ALLEGRO_BITMAP* back);

	// deleted function to make sure they are unacceptable
	// in order to be sure we dont get copies of the singleton
	TerrainStartScreen(TerrainStartScreen const&) = delete;
	void operator=(TerrainStartScreen const&) = delete;
	
	
private:
	TerrainStartScreen();
	~TerrainStartScreen();

	// bg image is scrollable
	int offsetBg;
	ALLEGRO_BITMAP* image = NULL;
	ALLEGRO_BITMAP* stopWarsImg = NULL;

	ALLEGRO_FONT titleFont;
	std::string titleText;
	ALLEGRO_COLOR titleColor;

	int textAlign;
	bool textVisible;
	
	/* mike geig - parallax bg */
	float x;
	float y;
	float velX;
	float velY;
	int dirX;
	int dirY;

	int width;
	int height;
	
};

#endif