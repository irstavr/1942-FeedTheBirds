#ifndef MOVINGPATHANIMATION_H
#define MOVINGPATHANIMATION_H

#include "Animation.h"
#include <list>

typedef unsigned int frame_t;

struct PathEntry {
	offset_t dx, dy;
	bool v_flip, h_flip;
	frame_t frame;
	delay_t	delay;

	PathEntry(void) : 
		dx(0), 
		dy(0), 
		h_flip(false), 
		v_flip(false), 
		frame(0xff), 
		delay(0) {
	};
	
	PathEntry(const PathEntry& p) :
		dx(p.dx), 
		dy(p.dy), 
		h_flip(p.h_flip), 
		v_flip(p.v_flip), 
		frame(p.frame), 
		delay(p.delay) {
	};
	
	PathEntry(offset_t _dx, 
			offset_t _dy, 
			bool _h_flip, 
			bool _v_flip, 
			frame_t _frame, 
			delay_t _delay) :
		dx(_dx), 
		dy(_dy), 
		h_flip(_h_flip), 
		v_flip(_v_flip), 
		frame(_frame), 
		delay(_delay) {
	};
};

class MovingPathAnimation : public Animation {
	std::list<PathEntry> path;
public:
	MovingPathAnimation(const std::list<PathEntry>& _path, animid_t id);
	~MovingPathAnimation();
	std::list<PathEntry>::iterator getFirstPathEntry(void);
	std::list<PathEntry>::iterator getLastPathEntry(void);
	void setPath(const std::list<PathEntry>& p);
	Animation* clone(animid_t newId) const;
};

#endif
