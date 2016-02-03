#ifndef ANIMATIONFILMHOLDER_H
#define ANIMATIONFILMHOLDER_H

#include "allegro5\allegro.h"
#include <map>
#include <string>
#include <cassert>
#include <vector>
#include <iostream>
#include <fstream>

#include "AnimationFilm.h"
#include "BitmapLoader.h"

class AnimationFilmHolder {
private:
	typedef std::map<std::string, AnimationFilm*> FilmMap;
	FilmMap filmMap;
	static AnimationFilmHolder *animationFH; //singleton instance

	static std::vector<AnimationFilm> filmMem; //films allocated as array
	std::vector<Rect> read_bboxes(const char* path, int framesNo);


	// deleted function to make sure they are unacceptable
	// in order to be sure we dont get copies of the singleton
	AnimationFilmHolder(AnimationFilmHolder const&) = delete;
	void operator=(AnimationFilmHolder const&) = delete;
	
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