#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include "..\Objects\Object.h"
#include "..\Animator\Animator.h"
#include "..\Sprites\Sprite.h"
#include "..\Utilities\Utilities.h"

class Terrain {
private:

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

public:

	Terrain();
	~Terrain();

	float x;
	float y;
	float velX;
	float velY;
	int dirX;
	int dirY;
	int width;
	int height;

	ALLEGRO_BITMAP* bgImage = NULL;
	ALLEGRO_BITMAP* remainingLivesImage = NULL;
	ALLEGRO_BITMAP* remainingLoopsImage = NULL;
	ALLEGRO_FONT *font1, *font2, *font3;
	ALLEGRO_COLOR bright_green;
	ALLEGRO_COLOR grey;
	const char* font_file;

	void updateBackground();
	void drawBackground(int highscore, int score, int lives, int loops);
	float getTerrainX();
	// deleted function to make sure they are unacceptable
	// in order to be sure we dont get copies of the singleton
	Terrain(Terrain const&) = delete;
	void operator=(Terrain const&) = delete;
};

#endif