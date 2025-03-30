#ifndef COMMON_FUNC__
#define COMMON_FUNC__
#include <SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include<string.h>
#include<vector>
#include<iostream>
#include<string>

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;
static Mix_Music *music;
static bool volume_on;
// screen
const int SCREEN_WIDTH = 1138;
const int SCREEN_HEIGHT = 640;

const int origin_x = 100;
const int origin_y = 430;
#define TILE_SIZE 30
#define MAX_MAP_x 19
#define MAX_MAP_y 18
#define Gravity 9.8
static bool playing;
struct Map
{
    int index_x;
    int index_y;
    int tile[MAX_MAP_y][MAX_MAP_x];
    char* filename;

};

#endif // COMMON_FUNC__
