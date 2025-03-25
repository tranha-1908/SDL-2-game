#ifndef COMMON_FUNC__
#define COMMON_FUNC__

#include <SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include<string.h>
#include<cmath>
#include<vector>
#include<iostream>
#include<string>

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;


// screen
const int SCREEN_WIDTH = 1138;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

#define TILE_SIZE 40
#define MAX_MAP_x 20
#define MAX_MAP_y 14

struct Map
{
    int start_x_;
    int start_y_;
    int index_x;
    int index_y;
    int tile[MAX_MAP_y][MAX_MAP_x];
    char* filename;
};



#endif // COMMON_FUNC__
