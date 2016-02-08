#include "../../include/GameAction/AudioHolder.h"
#include <string.h>

std::vector<ALLEGRO_SAMPLE *> AudioHolder::samples;
ALLEGRO_SAMPLE_ID* AudioHolder::music_id;
ALLEGRO_SAMPLE_ID* AudioHolder::sample_id;

AudioHolder::AudioHolder(void) {}

AudioHolder::~AudioHolder(void) {
	for(size_t i=0; i<samples.size(); ++i)
		al_destroy_sample(samples[i]);
}

bool AudioHolder::initialize(void) {
	music_id = new ALLEGRO_SAMPLE_ID();
	sample_id = new ALLEGRO_SAMPLE_ID();
	samples.push_back(al_load_sample("1942-FeedTheBirds\\data\\Audio\\Intro.ogg"));
	samples.push_back(al_load_sample("1942-FeedTheBirds\\data\\Audio\\mine.ogg"));
	samples.push_back(al_load_sample("1942-FeedTheBirds\\data\\Audio\\fart.ogg"));
	samples.push_back(al_load_sample("1942-FeedTheBirds\\data\\Audio\\splat.ogg"));
	samples.push_back(al_load_sample("1942-FeedTheBirds\\data\\Audio\\Anakins_Dark_Deeds.ogg"));
	samples.push_back(al_load_sample("1942-FeedTheBirds\\data\\Audio\\Hail_to_the_Winner_Anakin_Skywalker.ogg"));
	samples.push_back(al_load_sample("1942-FeedTheBirds\\data\\Audio\\Destiny_Islands.ogg"));
	al_reserve_samples(2);
	return true;
}

void AudioHolder::changeToSound(const char *mode) {
	al_stop_sample(sample_id);
	if(strcmp(mode, "intro") == 0) {
		//cout << "changeToSound!! \n";
		al_stop_samples();
		al_play_sample(samples[0], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, music_id);
	}
	else if(strcmp(mode, "scared") == 0) {
		//al_stop_samples();
		al_play_sample(samples[1], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, sample_id);
	}
	else if(strcmp(mode, "shoot") == 0) {
		//al_stop_samples();
		al_play_sample(samples[2], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, sample_id);
	}
	else if (strcmp(mode, "damage") == 0) {
		//al_stop_samples();
		al_play_sample(samples[3], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, sample_id);
	}
	else if (strcmp(mode, "gameover") == 0) {
		al_stop_samples();
		al_play_sample(samples[4], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, music_id);
	}
	else if (strcmp(mode, "victory") == 0) {
		al_stop_samples();
		al_play_sample(samples[5], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, music_id);
	}
	else if (strcmp(mode, "game") == 0) {
		al_stop_samples();
		al_play_sample(samples[6], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, music_id);
	}
}


void AudioHolder::stop() {
	al_stop_samples();
}
