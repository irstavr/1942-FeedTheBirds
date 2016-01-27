#ifndef FRAMERANGEANIMATION_H
#define FRAMERANGEANIMATION_H

#include "MovingAnimation.h"

typedef unsigned int frame_t;

class FrameRangeAnimation : public MovingAnimation {
    frame_t start, end;
public:
	FrameRangeAnimation(frame_t s, frame_t e, offset_t dx, offset_t dy, delay_t d, bool c, animid_t id);
    frame_t	getStartFrame(void) const;
    void setStartFrame(frame_t v);
    frame_t	getEndFrame(void) const;
    void setEndFrame(frame_t v);
	void setNewOffsets(offset_t dx, offset_t dy);
	FrameRangeAnimation* clone(animid_t newId) const;
};

#endif