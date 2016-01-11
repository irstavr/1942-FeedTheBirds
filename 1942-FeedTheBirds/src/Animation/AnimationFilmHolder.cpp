#include "../../include/Animation/AnimationFilmHolder.h"

using namespace std;

AnimationFilmHolder *AnimationFilmHolder::animationFH = NULL;

AnimationFilmHolder::AnimationFilmHolder(const char* path) {
	char buff[512], ch = ' ', bitmap[50], bboxes[50], id[50];
	int frames = 1;
	BitmapLoader bitmapLoader;
	ifstream cfg(path);
	while (!cfg.eof()) {
		ch = cfg.peek();
		if (ch != '#' && ch != '\n') {
			cfg.getline(buff, 512);
			sscanf(buff, "bitmap=%s id=%s frames=%d bboxes=%s", bitmap, id, &frames, bboxes);
			fprintf(stderr, "%s %d %d %s\n",  bitmap, id, frames, bboxes);
			AnimationFilm* anim_f = new AnimationFilm(bitmapLoader.load(bitmap), read_bboxes(bboxes, frames), id);
			filmMap[id] = anim_f;
		}
		else {
			cfg.ignore(512, '\n');
		}
		ch = cfg.peek();
		if (ch == ' ') break;
	}
	cfg.close();
	//AnimationFilm* anim_f = new AnimationFilm(bitmapLoader.load("1942-FeedTheBirds\\data\\Bitmaps\\superAce.png"), read_bboxes(bboxes, frames), "superAceAF");
	//filmMap["superAceAF"] = anim_f;
}

AnimationFilmHolder::~AnimationFilmHolder() {
	filmMap.clear();
	//delete[] filmMem; 
}

vector<Rect> AnimationFilmHolder::read_bboxes(const char* path, int framesNo) {
	char buff[512], ch = ' ';
	int x, y, w, h;
	vector<Rect> vect;
	Rect bbox(0, 0, 80, 80);
	vect.push_back(bbox);
	ifstream cfg(path);
	for (int i = 0; i < framesNo; i++) {
		cfg.getline(buff, 512);
		sscanf(buff, "x=%d y=%d w=%d h=%d", &x, &y, &w, &h);
		Rect bbox(x, y, w, h);
		vect.push_back(bbox);
	}
	cfg.close();
	return vect;
}

void AnimationFilmHolder::initialize(const char *path) {
	if (animationFH == NULL)
		animationFH = new AnimationFilmHolder(path);
}

AnimationFilmHolder *AnimationFilmHolder::getSingleton(void) {
	assert(animationFH);
	return animationFH;
}

const AnimationFilm *AnimationFilmHolder::getFilm(const std::string id) const {
	FilmMap::const_iterator i = filmMap.find(id);
	//assert(i != filmMap.end());
	return i->second;
}

