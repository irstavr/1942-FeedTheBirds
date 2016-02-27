#include "../../include/Animation/AnimationFilmHolder.h"

using namespace std;

// for linker
AnimationFilmHolder *AnimationFilmHolder::animationFH = NULL;
FilmMap AnimationFilmHolder::filmMap;

namespace AnimationHolderDelete {
	struct DeleteAnimation {
		void operator()(std::pair<std::string, AnimationFilm*> _pair) {
			assert(_pair.second);
			delete _pair.second;
			_pair.second = (AnimationFilm * )0;
		}
	};
}

AnimationFilmHolder::~AnimationFilmHolder() {
	assert(!filmMap.empty());
	std::for_each(filmMap.begin(),
		filmMap.end(),
		AnimationHolderDelete::DeleteAnimation());

	filmMap.clear();
	BitmapLoader::singletonDestroy();
}

void AnimationFilmHolder::singletonCreate(const char *path) {
	if (animationFH == NULL)
		animationFH = new AnimationFilmHolder(path);
}

void AnimationFilmHolder::singletonDestroy(void) {
	delete animationFH;
	animationFH = 0;
}

AnimationFilmHolder *AnimationFilmHolder::getSingleton(void) {
	assert(animationFH);
	return animationFH;
}

AnimationFilmHolder::AnimationFilmHolder(const char* path) {
	char buff[1412], bitmap[500], bboxes[500], id[500];
	int frames;
	//BitmapLoader bitmapLoader;
	BitmapLoader::singletonCreate();

	ifstream cfg(path);

	while (!cfg.eof()) {
		char ch = cfg.peek();
		if (ch != '#' && ch != '\n') {
			cfg.getline(buff, 1412);
			sscanf(buff, "bitmap=%499s id=%499s frames=%3d bboxes=%499s", bitmap, id, &frames, bboxes);
			//std::cerr << bitmap << " " << id << " " << frames << " " << bboxes << " " << endl;
			
			ALLEGRO_BITMAP* b_bitmap = BitmapLoader::load(bitmap);
			assert(bitmap);
			AnimationFilm* anim_f = new AnimationFilm(b_bitmap, read_bboxes(bboxes, frames), id);
			filmMap[id] = anim_f;
		}
		else {
			cfg.ignore(1412, '\n');
		}
		ch = cfg.peek();
		if (ch == ' ') break;
	}
	cfg.close();
}

vector<Rect> AnimationFilmHolder::read_bboxes(const char* path, int framesNo) {
	char buff[512];
	int x, y, w, h;
	vector<Rect> vect;
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

const AnimationFilm *AnimationFilmHolder::getFilm(const std::string &id) const {
	FilmMap::const_iterator i = filmMap.find(id);
	return i->second;
}

