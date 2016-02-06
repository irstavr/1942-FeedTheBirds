#include "../../include/Animation/BitmapLoader.h"

//for the linker
BitmapLoader* BitmapLoader::singletonPtr = (BitmapLoader*)0;
BitmapMap BitmapLoader::bitmaps;

namespace BitmapLoaderDelete {
	struct DeleteBitmap {
		void operator()(std::pair<std::string, ALLEGRO_BITMAP*> _pair) {
			al_destroy_bitmap(_pair.second);
		}
	};
}

BitmapLoader::BitmapLoader(void) {
}

BitmapLoader::~BitmapLoader() {
	// Destroy all bitmaps in the map.
	std::for_each(bitmaps.begin(),
		bitmaps.end(),
		BitmapLoaderDelete::DeleteBitmap());
	bitmaps.clear();
}

void BitmapLoader::singletonCreate(void) {
	singletonPtr = new BitmapLoader();
}

void BitmapLoader::singletonDestroy(void) {
	assert(singletonPtr);
	delete singletonPtr;
	singletonPtr = 0;
}

ALLEGRO_BITMAP* BitmapLoader::loadBitmap(const std::string& path) {
	ALLEGRO_BITMAP *bitmap = al_load_bitmap(path.c_str());
	if (!bitmap) {
		al_show_native_message_box(al_get_current_display(), "Error", "Error", ("Could not load bitmap file " + path + "\n").c_str(), NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(1);
	}
	assert(bitmap);
	return bitmap;
}

ALLEGRO_BITMAP* BitmapLoader::getBitmap(const std::string& path) {
	BitmapMap::const_iterator i = bitmaps.find(path);
	return i != bitmaps.end() ? i->second : NULL;
}

ALLEGRO_BITMAP* BitmapLoader::load(const std::string& path) {
	ALLEGRO_BITMAP *b = getBitmap(path);
	if (!b) {
		bitmaps[path] = (b = loadBitmap(path));
		assert(b);
	}
	return b;
}