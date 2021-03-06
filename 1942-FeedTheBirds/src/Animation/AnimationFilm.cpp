#include "../../include/Animation/AnimationFilm.h"

AnimationFilm::AnimationFilm(ALLEGRO_BITMAP *b, 
							const std::vector<Rect>& bx, 
							const std::string& _id) :
		bitmap(b), 
		boxes(bx), 
		id(_id) 
{
	frameWidth = al_get_bitmap_width(bitmap)/boxes.size();
	frameHeight = al_get_bitmap_height(bitmap);
}

byte AnimationFilm::getTotalFrames(void) const { 
	return (byte)boxes.size();
}

ALLEGRO_BITMAP* AnimationFilm::getBitmap(void) const { 
	return bitmap; 
}

const std::string AnimationFilm::getId(void) const { 
	return id; 
}

const Rect AnimationFilm::getFrameBox(byte frameNo) const {
	Rect frame(frameNo*frameWidth,0,frameWidth,frameHeight);
	return frame;
}

const Rect AnimationFilm::getBoundingBox(byte frameNo) const {
	//	assert(boxes.size() > frameNo);
	if (boxes.size() <= frameNo)
		frameNo = 0; //reset
	return boxes[frameNo];
}

void AnimationFilm::displayFrame(const Point& at, byte frameNo, bool flip_h, bool flip_v) const {
	if (frameNo >= 0) {
		Rect sprite = getFrameBox(frameNo);
		ALLEGRO_BITMAP *bmp = al_create_sub_bitmap(bitmap, sprite.x, sprite.y, sprite.w, sprite.h);
		al_draw_scaled_rotated_bitmap(bmp, 0, 0, at.x, at.y, 2, 2, 0,
			(flip_h ? ALLEGRO_FLIP_HORIZONTAL : 0) | (flip_v ? ALLEGRO_FLIP_VERTICAL : 0));
	}
}