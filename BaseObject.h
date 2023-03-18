#ifndef baseObject_H_
#define baseObject_H_

#include "CommonFunction.h"

typedef struct sBaseObject BaseObject;
struct sBaseObject
{
	SDL_Texture* object; //core cua 1 object
	SDL_Rect objectRect; //kich thuoc cua 1 object

	void (*Destroy) (BaseObject*); //giai phong object
	void (*SetRect) (BaseObject*, const int, const int); //set kich thuoc
	SDL_Rect(*GetRect) (const BaseObject*); //get kich thuoc
	SDL_Texture* (*GetObject) (const BaseObject*); //get object
	bool (*LoadImg) (BaseObject*, const char*, SDL_Renderer*); //load hinh anh cho object
	void (*Render) (BaseObject*, SDL_Renderer*, const SDL_Rect*); //render object len screen 
	void (*Free) (BaseObject*); //giai phong
};

BaseObject BaseObject_Create();
void BaseObject_Destroy(BaseObject* obj);
void BaseObject_SetRect(BaseObject* obj, const int x, const int y);
SDL_Rect BaseObject_GetRect(const BaseObject* obj);
SDL_Texture* BaseObject_GetObject(const BaseObject* obj);
bool BaseObject_LoadImg(BaseObject* obj, const char* path, SDL_Renderer* screen);
void BaseObject_Render(BaseObject* obj, SDL_Renderer* des, const SDL_Rect* clip);
void BaseObject_Free(BaseObject* obj);

#endif // !baseObject_H_