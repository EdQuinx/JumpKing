#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "CommonFunction.h"


typedef struct {
    SDL_Rect window;
    SDL_Rect bounds;
} Camera;

void camera_init(Camera* camera, int x, int y, int w, int h);
void camera_move(Camera* camera, int x, int y);
SDL_Rect camera_transform(const Camera* camera, const SDL_Rect* rect);
void camera_set_bounds(Camera* camera, int x, int y, int w, int h);
void camera_center(Camera* camera, int x, int y);

#endif // CAMERA_H_INCLUDED
