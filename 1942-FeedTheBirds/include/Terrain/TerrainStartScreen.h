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

#include "Terrain.h"

#define PIXEL_SCROLL_PER_CYCLE 5

class TerrainStartScreen : public Terrain {

public:
	static TerrainStartScreen& getInstance();

	// deleted function to make sure they are unacceptable
	// in order to be sure we dont get copies of the singleton
	TerrainStartScreen(TerrainStartScreen const&) = delete;
	void operator=(TerrainStartScreen const&) = delete;
	void TerrainStartScreen::drawBackground(float SCREEN_WINDOW_HEIGHT);

private:
	TerrainStartScreen();
	~TerrainStartScreen();
	ALLEGRO_BITMAP* stopWarsImage = NULL;
	
};

#endif