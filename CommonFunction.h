#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

static SDL_Window* g_windows = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

//Screen
const int FRAME_PER_SECOND;
const int SCREEN_WIDTH;
const int SCREEN_HEIGHT;
const int SCREEN_BPP;

const int COLOR_KEY_R;
const int COLOR_KEY_G;
const int COLOR_KEY_B;

const int RENDERER_DRAW_COLOR;

#define BLANK_TILE 0
#define TILE_SIZE 64

#define MAX_MAP_X 400
#define MAX_MAP_Y 10

#define STATE_MONEY 4

typedef struct Input {
	int left;
	int right;
	int up;
	int down;
	int jump;
} Input;

typedef struct Map {
	int startX;
	int startY;

	int maxX;
	int maxY;

	int tile[MAX_MAP_Y][MAX_MAP_X];
	char* fileName;
} Map;

#endif // !COMMON_FUNCTION_H_
