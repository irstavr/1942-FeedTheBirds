#ifndef AUDIOHOLDER_H
#define AUDIOHOLDER_H

#include "../Utilities/Utilities.h"
#include <stdio.h>
#include <vector>
#include "../Sprites/Sprite.h"

using namespace std;

class AudioHolder {
private:
	static std::vector<ALLEGRO_SAMPLE *>samples;
	static ALLEGRO_SAMPLE_ID *sample_id;

public:
	AudioHolder(void);
	~AudioHolder(void);

	static bool initialize(void);
	static void changeToSound(const char *);
	static void registerSound(Sprite *, char *name);
	static void pause(void);
	static void changeToSound(Sprite *, char *name);
	static void start(Sprite *);
	static void stop();
};

#endif