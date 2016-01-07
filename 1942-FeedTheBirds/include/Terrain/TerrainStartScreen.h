#ifndef _TERRAIN_START_SCREEN_H_
#define _TERRAIN_START_SCREEN_H_

#include "Terrain.h"
#define PIXEL_SCROLL_PER_CYCLE 5

class TerrainStartScreen : public Terrain {

public:
	static TerrainStartScreen& getInstance();

	// deleted function to make sure they are unacceptable
	// in order to be sure we dont get copies of the singleton
	TerrainStartScreen(TerrainStartScreen const&) = delete;
	void operator=(TerrainStartScreen const&) = delete;

	void updateBackground();
	void drawBackground();

private:
	TerrainStartScreen();
	~TerrainStartScreen();
	ALLEGRO_BITMAP* stopWarsImage = NULL;
	
};

#endif