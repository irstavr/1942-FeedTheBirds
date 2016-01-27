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

#define GAME_STATE_INTRO 0
#define GAME_STATE_MAINGAME 1
#define GAME_STATE_PAUSED 2
#define GAME_STATE_GAMEOVER 3
#define GAME_STATE_FINISHED 4

#define TERRAIN_IMAGE_WIDTH 9270*3
#define TERRAIN_IMAGE_HEIGHT 669

#define FPS 120
#define LPS 120

typedef int Dim;
typedef unsigned char byte;
typedef std::pair<int, int> COORDS;

/* get system current time */
extern unsigned int getCurrTime(void);


#endif