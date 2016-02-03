#include "../../include/Animation/Animation.h"

Animation::Animation(animid_t _id) : id(_id) {
	assert(_id>=0);
}

animid_t Animation::getId(void) {
	assert(id>0);
	return id;
}

Animation::~Animation() {
	id = -1;
}