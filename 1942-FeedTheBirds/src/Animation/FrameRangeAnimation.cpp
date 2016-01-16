#include "../../include/Animation/FrameRangeAnimation.h"

FrameRangeAnimation::FrameRangeAnimation (
        frame_t s, frame_t e, 
        offset_t dx, offset_t dy, delay_t d, bool c, animid_t id
    ): 
	start(s), 
	end(e), 
	MovingAnimation(dx, dy, d, c, id)	{
}

frame_t	FrameRangeAnimation::getStartFrame(void) const { 
	return start; 
}
    
void FrameRangeAnimation::setStartFrame(frame_t v) { 
	start = v; 
}
    
frame_t	FrameRangeAnimation::getEndFrame(void) const { 
	return end; 
}
    
void FrameRangeAnimation::setEndFrame(frame_t v) { 
	end = v; 
}
    
Animation* FrameRangeAnimation::clone(animid_t newId) const {
	return new FrameRangeAnimation(start, end, getDx(), getDy(), getDelay(), getContinuous(), newId);
}
