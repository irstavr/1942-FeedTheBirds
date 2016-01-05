#ifndef ANIMATIONFILM_H
#define ANIMATIONFILM_H

#include "allegro5\allegro.h"
#include <vector>
#include "windows.h"

#include "..\Objects\Object.h"

class AnimationFilm {
	std::vector<Rect> boxes;
	ALLEGRO_BITMAP *bitmap;
	std::string	id;
public:

	AnimationFilm();
	AnimationFilm(ALLEGRO_BITMAP *, const std::vector<Rect>, const std::string&);
	
	byte getTotalFrames(void) 	const;
	ALLEGRO_BITMAP *getBitmap(void) const;
	const std::string getId(void) const;
	const Rect getFrameBox(byte frameNo) const;
	void displayFrame(const Point& at, byte frameNo, bool flip_h, bool flip_v) const;
};

#endif