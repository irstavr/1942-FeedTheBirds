#include "../../include/Animation/BitmapLoader.h"

#include <cassert>
#include <allegro5/allegro_native_dialog.h>
#include <iostream>
BitmapLoader::BitmapLoader(void) {}

BitmapLoader::~BitmapLoader() {
	// Destroy all bitmaps in the map.
	bitmaps.clear();
}

ALLEGRO_BITMAP *loadBitmap(const std::string& path) {
	ALLEGRO_BITMAP *bitmap = al_load_bitmap(path.c_str());
	if (!bitmap) {
		fprintf(stderr, "Could not load bitmap file %s", path);
		al_show_native_message_box(al_get_current_display(), "Error", "Error", ("Could not load bitmap file " + path + "\n").c_str(), NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(1);
	}
	//al_convert_mask_to_alpha(bitmap, al_map_rgb(0, 64, 128));
	return bitmap;
}

void destroyBitmap(ALLEGRO_BITMAP *bitmap) {
	al_destroy_bitmap(bitmap);
}

ALLEGRO_BITMAP* BitmapLoader::getBitmap(const std::string path) const {
	BitmapMap::const_iterator i = bitmaps.find(path);
	return i != bitmaps.end() ? i->second : NULL;
}

ALLEGRO_BITMAP* BitmapLoader::load(const std::string& path) {
	ALLEGRO_BITMAP *b = getBitmap(path);
	std::cout << "path=" << path << "\n";
	if (!b) {
		bitmaps[path] = (b = loadBitmap(path));
		assert(b);
	}
	return b;
}