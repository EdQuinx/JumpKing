#include "BaseObject.h"

//init 
BaseObject BaseObject_Create()
{
	BaseObject obj;
	obj.object = NULL;
	obj.objectRect.x = 0;
	obj.objectRect.y = 0;
	obj.objectRect.w = 0;
	obj.objectRect.h = 0;
	obj.Destroy = BaseObject_Destroy;
	obj.SetRect = BaseObject_SetRect;
	obj.GetRect = BaseObject_GetRect;
	obj.GetObject = BaseObject_GetObject;
	obj.LoadImg = BaseObject_LoadImg;
	obj.Render = BaseObject_Render;
	obj.Free = BaseObject_Free;
	return obj;
}

void BaseObject_Destroy(BaseObject* obj)
{
	if (obj)
	{
		BaseObject_Free(obj);
	}
}


void BaseObject_SetRect(BaseObject* obj, const int x, const int y)
{
	obj->objectRect.x = x;
	obj->objectRect.y = y;
}

SDL_Rect BaseObject_GetRect(const BaseObject* obj)
{
	return obj->objectRect;
}

SDL_Texture* BaseObject_GetObject(const BaseObject* obj)
{
	return obj->object;
}

bool BaseObject_LoadImg(BaseObject* obj, const char* path, SDL_Renderer* screen)
{
	BaseObject_Free(obj);
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadSurface = IMG_Load(path);
	if (loadSurface != NULL)
	{
		SDL_SetColorKey(loadSurface, SDL_TRUE, SDL_MapRGB(loadSurface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
		newTexture = SDL_CreateTextureFromSurface(screen, loadSurface);
		if (newTexture != NULL)
		{
			obj->objectRect.w = loadSurface->w;
			obj->objectRect.h = loadSurface->h;
		}

		SDL_FreeSurface(loadSurface);
	}
	obj->object = newTexture;

	return obj->object != NULL;
}

void BaseObject_Render(BaseObject* obj, SDL_Renderer* des, const SDL_Rect* clip)
{
	SDL_Rect quadRect = { 
		obj->objectRect.x, 
		obj->objectRect.y, 
		obj->objectRect.w, 
		obj->objectRect.h 
	};
	SDL_RenderCopy(des, obj->object, clip, &quadRect);
}

void BaseObject_Free(BaseObject* obj) {
    if (obj->object != NULL) {
        //SDL_DestroyTexture(obj->object);
        obj->object = NULL;
        obj->objectRect.h = 0;
        obj->objectRect.w = 0;
    }
}