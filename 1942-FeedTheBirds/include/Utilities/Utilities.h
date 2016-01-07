#ifndef UTILITIES_H
#define UTILITIES_H

#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <list>

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h> 
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#define START_SCREEN_WINDOW_WIDTH  640
#define START_SCREEN_WINDOW_HEIGHT 480

#define SCREEN_WINDOW_WIDTH  1300
#define SCREEN_WINDOW_HEIGHT 669

namespace Utilities {

	/* get system current time */
	unsigned int getCurrTime();

};



#endif