#include "..\..\include\Animation\MovingPathAnimation.h"

MovingPathAnimation::MovingPathAnimation(const std::list<PathEntry>& _path, 
										animid_t id) :
	path(_path), Animation(id) {
}

MovingPathAnimation::~MovingPathAnimation(void) {
	path.clear();
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

std::list<PathEntry>* createSmoothDiagonalPath(int dx, int dy) {//close enough
	std::list<PathEntry> *paths = new std::list<PathEntry>;
	int sumx, sumy, absx, absy;
	sumx = 0;
	sumy = 0;
	absx = (dx < 0 ? -dx : dx);
	absy = (dy < 0 ? -dy : dy);

	if (absx > absy) {
		for (;sumx<absx;) {
			paths->push_back(PathEntry((dx < 0 ? -1 : 1), (int)(dy < 0 ? -1 : 1), false, false, 0, 12));
			//cout << "1Just added dx=" << paths->back().dx << " dy=" << paths->back().dy << endl;
			sumy++;
			sumx++;
		}
		for (;sumy < absy;sumy++) {
			paths->push_back(PathEntry(0, (dy < 0 ? -1 : 1), false, false, 0, 12));
			//cout << "3Just added dx=" << paths->back().dx << " dy=" << paths->back().dy << endl;
		}
	}
	else {
		for (;sumy<absy;) {
			paths->push_back(PathEntry((dx < 0 ? -1 : 1), (dy < 0 ? -1 : 1), false, false, 0, 12));
			//cout << "4Just added dx=" << paths->back().dx << " dy=" << paths->back().dy << endl;
			sumx++;
			sumy++;
		}
		for (;sumx < absx;sumx++) {
			paths->push_back(PathEntry((dx < 0 ? -1 : 1), 0, false, false, 0, 12));
			//cout << "6Just added dx=" << paths->back().dx << " dy=" << paths->back().dy << endl;
		}
	}
	std::vector<PathEntry> tmpVector(paths->size());
	copy(paths->begin(), paths->end(), tmpVector.begin());
	std::random_shuffle(tmpVector.begin(), tmpVector.end());
	copy(tmpVector.begin(), tmpVector.end(), paths->begin());
	return paths;
}

std::list<PathEntry>* createCircularPath(int radius, int startAngle, int endAngle) {
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
				false, false, 0, 25));
		lastx = XforCircle(radius);
		lasty = YforCircle(radius);
		//cout << "Just added dx=" << paths->back().dx << " dy=" << paths->back().dy << endl;
	}
	paths->push_back(PathEntry(0, 0, false, false, 0, 0));
	return paths;
}