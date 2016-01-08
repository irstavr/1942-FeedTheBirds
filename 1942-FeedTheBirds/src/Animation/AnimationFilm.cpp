#include "../../include/Animation/AnimationFilm.h"

AnimationFilm::AnimationFilm(ALLEGRO_BITMAP *b, const std::vector<Rect> bx, const std::string& _id) :
	bitmap(b), boxes(bx), id(_id) {}

byte AnimationFilm::getTotalFrames(void) const { return boxes.size(); }

const Rect AnimationFilm::getFrameBox(byte frameNo) const {
	//TODO 
	return boxes[frameNo];
}