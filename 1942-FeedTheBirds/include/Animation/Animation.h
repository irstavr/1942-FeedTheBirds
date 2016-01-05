#ifndef ANIMATION_H
#define ANIMATION_H

typedef signed char	offset_t;
typedef unsigned short delay_t;
typedef unsigned short animid_t;

class Animation {

private:
	animid_t id;

public:
	Animation(animid_t _id) : id(_id) {
	}

	virtual ~Animation() {}

	animid_t getId(void) { 
		return id; 
	}
	virtual Animation* clone(animid_t newId) const = 0;
	
};

#endif