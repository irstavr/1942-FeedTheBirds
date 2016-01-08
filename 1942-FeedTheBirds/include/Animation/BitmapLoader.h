#ifndef BITMAPLOADER_H
#define BITMAPLOADER_H

#include "allegro5\allegro.h"

#include <string>
#include <map>

ALLEGRO_BITMAP *loadBitmap(const std::string& path);
void destroyBitmap(ALLEGRO_BITMAP);

class BitmapLoader {
	typedef std::map<std::string, ALLEGRO_BITMAP *> BitmapMap;
	BitmapMap bitmaps;
	ALLEGRO_BITMAP *getBitmap(const std::string path) const;
public:
	ALLEGRO_BITMAP *load(const std::string& path);
	BitmapLoader(void);
	~BitmapLoader();
};

#endif