#include "..\..\include\Animation\MovingPathAnimation.h"

MovingPathAnimation::MovingPathAnimation(const std::list<PathEntry>& _path, 
										animid_t id) :
	path(_path), Animation(id) {
}

std::list<PathEntry>::iterator 
MovingPathAnimation::getFirstPathEntry(void) { 
	return path.begin(); 
}

std::list<PathEntry>::iterator 
MovingPathAnimation::getLastPathEntry(void) { 
	return path.end(); 
}

void MovingPathAnimation::setPath(const std::list<PathEntry>& p) 
{
	path.clear(); path = p;
}

Animation* MovingPathAnimation::clone(animid_t newId) const {
	return new MovingPathAnimation(path, newId);
}
