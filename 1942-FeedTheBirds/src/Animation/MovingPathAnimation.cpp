#include "..\..\include\Animation\MovingPathAnimation.h"

MovingPathAnimation::MovingPathAnimation(const std::list<PathEntry>& _path, 
										animid_t id) :
	path(_path), Animation(id) {
}

MovingPathAnimation::~MovingPathAnimation(void) {
	path.clear();
	path = (std::list<PathEntry>) 0;
}

std::list<PathEntry>::iterator 
MovingPathAnimation::getFirstPathEntry(void) { 
	return path.begin(); 
}

std::list<PathEntry>::iterator 
MovingPathAnimation::getLastPathEntry(void) { 
	return path.end(); 
}

void MovingPathAnimation::setPath(const std::list<PathEntry>& p) {
	path.clear(); path = p;
}

MovingPathAnimation* MovingPathAnimation::clone(animid_t newId) const {
	return new MovingPathAnimation(path, newId);
}

std::list<PathEntry>* createSmoothDiagonalPath(int dx, int dy, delay_t delay) {//close enough
	std::list<PathEntry> *paths = new std::list<PathEntry>;
	int sumx, sumy, absx, absy;
	sumx = 0;
	sumy = 0;
	absx = (dx < 0 ? -dx : dx);
	absy = (dy < 0 ? -dy : dy);
	if (absx > absy) {
		for (; sumx < absx;) {
			if (absy != 0) {
				paths->push_back(PathEntry((dx < 0 ? -1 : 1), (int)(dy < 0 ? -1 : 1), false, false, 0, delay));
				sumy++;
			}
			else {
				paths->push_back(PathEntry((dx < 0 ? -1 : 1), 0, false, false, 0, delay));
			}
			sumx++;
		}
		for (; sumy < absy; sumy++) {
			if (absy != 0) {
				paths->push_back(PathEntry(0,(dy < 0 ? -1 : 1), false, false, 0, delay));
			}
			else {
				paths->push_back(PathEntry(0, 0, false, false, 0, delay));
			}
		}
	}
	else {
		for (;sumy<absy;) {
			if (absx != 0) {
				paths->push_back(PathEntry((dx < 0 ? -1 : 1), (dy < 0 ? -1 : 1), false, false, 0, delay));
				sumx++;
			}
			else {
				paths->push_back(PathEntry(0, (dy < 0 ? -1 : 1), false, false, 0, delay));
			}
			sumy++;
		}
		for (;sumx < absx;sumx++) {
			if (absx != 0) {
				paths->push_back(PathEntry((dx < 0 ? -1 : 1), 0, false, false, 0, delay));
			}
		}
	}
	std::vector<PathEntry> tmpVector(paths->size());
	copy(paths->begin(), paths->end(), tmpVector.begin());
	std::random_shuffle(tmpVector.begin(), tmpVector.end());
	copy(tmpVector.begin(), tmpVector.end(), paths->begin());
	return paths;
}

std::list<PathEntry>* createCircularPath(int radius, int startAngle, int endAngle, delay_t delay) {
	std::list<PathEntry> *paths = new std::list<PathEntry>;
	int lastx, lasty, i;
	i = startAngle - 1;
	lastx = XforCircle(radius);
	lasty = YforCircle(radius);
	paths->push_back(PathEntry(0, 0, false, false, 0, 0));
	for (int i = startAngle; i < endAngle; i += 1) {
		paths->push_back(
			PathEntry(
				XforCircle(radius) - lastx,
				-(YforCircle(radius) - lasty),
				false, false, 0, delay));
		lastx = XforCircle(radius);
		lasty = YforCircle(radius);
	}
	paths->push_back(PathEntry(0, 0, false, false, 0, 0));
	return paths;
}

std::list<PathEntry>* createLoopCircularPath(int radius, int startAngle, int endAngle, delay_t delay, frame_t frame) {
	std::list<PathEntry> *paths = new std::list<PathEntry>;
	int lastx, lasty, i;
	i = startAngle - 1;
	lastx = XforCircle(radius);
	lasty = YforCircle(radius);
	paths->push_back(PathEntry(0, 0, false, false, frame, delay));
	for (int i = startAngle; i < endAngle; i += 1) {
		paths->push_back(
			PathEntry(
				XforCircle(radius) - lastx,
				-(YforCircle(radius) - lasty),
				false, false, frame, delay));
		lastx = XforCircle(radius);
		lasty = YforCircle(radius);
	}
	paths->push_back(PathEntry(0, 0, false, false, frame, delay));
	return paths;
}