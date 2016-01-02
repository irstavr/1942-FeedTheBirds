#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include <assert.h>
#include <list>
#include <allegro5\allegro5.h> 
#include "..\Objects\Object.h"
#include "..\Animator\Animator.h"
#include "..\Sprites\Sprite.h"

class Terrain {
private:
	Terrain();
	~Terrain();
	static Terrain* terrain; //sigleton

	/* discriminate background from terrain objects */
	float terrainWidth;
	float terrainHeight;
	float viewWinHeight;	//width==terrain width
	std::list<Sprite*> terrainObjects;	//init at beginning
	float startYPos; // for view window (initially: terrainHeight - viewWinHeight)

	static std::list<Sprite*> getVisibleObjects(); // returns list of objects on the view window

public:
	static void create() {}
	static void displayTerrain(ALLEGRO_BITMAP *, unsigned long) {}
	static void cleanUp() {}
	static Terrain* getTerrain() { return terrain; }
};

#endif