#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <list>
#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h> 
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_primitives.h>

#include "..\Objects\Object.h"
#include "..\Animator\Animator.h"
#include "..\Sprites\Sprite.h"

class Terrain {
private:
	static Terrain* terrain; //sigleton

	// bg image is scrollable
	int offsetBg;

	ALLEGRO_FONT titleFont;
	std::string titleText;
	ALLEGRO_COLOR titleColor;

	int textAlign;
	bool textVisible;

	/* discriminate background from terrain objects */
	float terrainWidth;
	float terrainHeight;
	float viewWinWidth;	//height==terrain height
	std::list<Sprite*> terrainObjects;	//init at beginning
	float startYPos; // for view window (initially: terrainHeight - viewWinHeight)

	static std::list<Sprite*> getVisibleObjects(); // returns list of objects on the view window

public:

	Terrain();
	~Terrain();

	/* mike geig - parallax bg */
	float x;
	float y;
	float velX;
	float velY;
	int dirX;
	int dirY;

	int width;
	int height;

	ALLEGRO_BITMAP* bgImage = NULL;
	ALLEGRO_FONT *font1, *font2;
	ALLEGRO_COLOR bright_green;

	const char* font_file;

	static void cleanUp() {}
	static Terrain& getInstance();

	void create(float x, float y, float velx, float vely, int width, int height, int dirX, int dirY);
	void updateBackground();
	void drawBackground(float SCREEN_WINDOW_HEIGHT);

};

#endif