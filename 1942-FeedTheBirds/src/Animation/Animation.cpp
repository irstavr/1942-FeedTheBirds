#include "../../include/Animation/Animation.h"

// TODO: enable latelyDestroyable
Animation::Animation(animid_t _id) :
	/*LatelyDestroyable(),*/ 
	id(_id) 
{
	assert(_id>=0);
}

animid_t Animation::getId(void) {
	assert(id>0);
	return id;
}

Animation :: ~Animation() {
	id = -1;
}