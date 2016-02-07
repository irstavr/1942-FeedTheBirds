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

typedef std::map<std::string, AnimationFilm*> FilmMap;

class AnimationFilmHolder {

public:
	static void singletonCreate(const char *path);
	static void singletonDestroy(void);
	static AnimationFilmHolder *getSingleton(void);
	const AnimationFilm *getFilm(const std::string &id) const;

private:
	static AnimationFilmHolder *animationFH; //singleton instance

	static FilmMap filmMap;

	std::vector<Rect> read_bboxes(const char* path, int framesNo);

	// deleted function to make sure they are unacceptable
	// in order to be sure we dont get copies of the singleton
	AnimationFilmHolder(AnimationFilmHolder const&) = delete;
	void operator=(AnimationFilmHolder const&) = delete;

	explicit AnimationFilmHolder(const char* path);
	~AnimationFilmHolder();

};
#endif