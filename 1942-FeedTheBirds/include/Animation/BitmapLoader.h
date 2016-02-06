#ifndef BITMAPLOADER_H
#define BITMAPLOADER_H

#include "allegro5\allegro.h"
#include <allegro5/allegro_native_dialog.h>

#include <algorithm> 
#include <cassert>
#include <iostream>
#include <string>
#include <map>

typedef std::map<std::string, ALLEGRO_BITMAP *> BitmapMap;

class BitmapLoader {

public:
	static void	singletonCreate(void);
	static void	singletonDestroy(void);
	static ALLEGRO_BITMAP *load(const std::string& path);

private:
	BitmapLoader(void);
	~BitmapLoader();

	static BitmapLoader* singletonPtr;
	static BitmapMap bitmaps;

	static ALLEGRO_BITMAP *loadBitmap(const std::string& path);
	static ALLEGRO_BITMAP *getBitmap(const std::string& path);

};

#endif