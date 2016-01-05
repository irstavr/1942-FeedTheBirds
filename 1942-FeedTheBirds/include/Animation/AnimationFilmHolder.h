#ifndef ANIMATIONFILMHOLDER_H
#define ANIMATIONFILMHOLDER_H

#include "allegro5\allegro.h"
#include <map>
#include <string>
#include <cassert>
#include <vector>

#include "AnimationFilm.h"

class AnimationFilmHolder {
private:
	std::map<std::string, AnimationFilm*> filmMap;
	static AnimationFilmHolder *animationFH; //singleton instance

	static std::vector<AnimationFilm> filmMem; //films allocated as array
	
protected:
	AnimationFilmHolder(const char* path); // Decoder constructor.
	~AnimationFilmHolder();

public:
	static void initialize(char const *path);
	static void destroy(void) { delete animationFH; };
	static AnimationFilmHolder *getSingleton(void);
	const AnimationFilm *getFilm(const std::string id) const;
};
#endif