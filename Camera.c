#include "camera.h"

void camera_init(Camera* camera, int x, int y, int w, int h) {
    camera->window.x = x;
    camera->window.y = y;
    camera->window.w = w;
    camera->window.h = h;
    camera->bounds.x = 0;
    camera->bounds.y = 0;
    camera->bounds.w = w;
    camera->bounds.h = h;
}

void camera_move(Camera* camera, int x, int y) {
    camera->window.x += x;
    camera->window.y += y;

    if (camera->window.x < camera->bounds.x) {
        camera->window.x = camera->bounds.x;
    }
    if (camera->window.y < camera->bounds.y) {
        camera->window.y = camera->bounds.y;
    }
    if (camera->window.x + camera->window.w > camera->bounds.x + camera->bounds.w) {
        camera->window.x = camera->bounds.x + camera->bounds.w - camera->window.w;
    }
    if (camera->window.y + camera->window.h > camera->bounds.y + camera->bounds.h) {
        camera->window.y = camera->bounds.y + camera->bounds.h - camera->window.h;
    }
}

SDL_Rect camera_transform(const Camera* camera, const SDL_Rect* rect) {
    SDL_Rect result = *rect;
    result.x -= camera->window.x;
    result.y -= camera->window.y;
    return result;
}

void camera_set_bounds(Camera* camera, int x, int y, int w, int h) {
    camera->bounds.x = x;
    camera->bounds.y = y;
    camera->bounds.w = w;
    camera->bounds.h = h;
}

void camera_center(Camera* camera, int x, int y) {
    camera_move(camera, x - camera->window.x - camera->window.w / 2, y - camera->window.y - camera->window.h / 2);
}
