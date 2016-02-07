#include "../../include/Animation/Animation.h"

Animation::Animation(animid_t _id) : 
		id(_id) {
}

animid_t Animation::getId(void) {
	assert(id>0);
	return id;
}

Animation::~Animation() {
	id = -1;
}