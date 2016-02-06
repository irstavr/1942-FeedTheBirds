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
	AnimationFilm(ALLEGRO_BITMAP *, const std::vector<Rect>, const std::string&);

	~AnimationFilm() {
		boxes.clear();
		// only bitmap loader can delte a bitmap !!!!
		bitmap = (ALLEGRO_BITMAP*)0;
		id.clear();
	}

	byte getTotalFrames(void) 	const;
	ALLEGRO_BITMAP *getBitmap(void) const;
	const std::string getId(void) const;
	const Rect getFrameBox(byte frameNo) const;
	const Rect getBoundingBox(byte frameNo) const;
	void displayFrame(const Point& at, byte frameNo, bool flip_h, bool flip_v) const;

private:
	int frameWidth;
	int frameHeight;
};

#endif