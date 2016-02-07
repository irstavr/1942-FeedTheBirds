#ifndef ANIMATION_H
#define ANIMATION_H

#include "allegro5\allegro.h"

typedef int	offset_t;
typedef unsigned short delay_t;
typedef unsigned int animid_t;

class Animation {

private:
	animid_t id;

public:
	explicit Animation(animid_t _id);
	virtual ~Animation();
	animid_t getId(void);
	virtual Animation* clone(animid_t newId) const = 0;
	
};

#endif