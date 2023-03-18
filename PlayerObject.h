#ifndef PLAYER_OBJECT_H_
#define PLAYER_OBJECT_H_

#include "BaseObject.h"
#include "CommonFunction.h"

#define GRAVITY_SPEED 0.6 //trong luc
#define MAX_FALL_SPEED 10 //toc do roi 
#define PLAYER_SPEED 4 //toc do di chuyen
#define PLAYER_JUMP_VAL 22 //toc do nhay

typedef struct sPlayerObject PlayerObject;
struct sPlayerObject {
	BaseObject baseObject;

	void (*Init)(PlayerObject*);//init
	void (*Destroy)(PlayerObject*);//giai phong
	bool (*LoadImg)(PlayerObject*, const char*, SDL_Renderer*);//load hinh anh
	void (*Render)(PlayerObject*, SDL_Renderer* des);//render ra screen
	void (*HandleInputAction)(PlayerObject*, SDL_Event, SDL_Renderer*);//event di chuyen
	void (*set_clips)(PlayerObject*);//animation
	void (*DoPlayer)(PlayerObject*, Map*);//di chuyen
	void (*CheckToMap)(PlayerObject*, Map*);//check camera
	void (*SetMapXY)(PlayerObject*, const int, const int);//set vi tri
	void (*CenterEntityOnMap)(PlayerObject*, Map*);//camera
	void (*UpdateImagePlayer)(PlayerObject*, SDL_Renderer*);//update hinh anh

	int money_count;
	//BulletObject** p_bullet_list_;

	//thong so khi di chuyen
	float moveValueX;
	float moveValueY;

	//truc
	float posX;
	float posY;

	int frameWidth;
	int frameHeight;

	SDL_Rect frameSprites[8];//hoat anh

	Input keyInputType;//key input
	int frame;//frame animate
	int playerStatus;//trang thai cua player
	bool isOnGround;//cham dat

	int mapX;
	int mapY;

	int frameTime;//time milisec

	int present_bullet_;
};

enum WalkType {
	WALK_NONE = 1,
	WALK_RIGHT = 2,
	WALK_LEFT = 3,
	jumpUP = 4,
	jumpLEFT = 5,
	jumpRIGHT = 6,
	FALL_DOWN = 7,
	FALL_LEFT = 8,
	FALL_RIGHT = 9
};

PlayerObject PlayerObject_Create();
void PlayerObject_Destroy(PlayerObject* obj);
bool PlayerObject_LoadImg(PlayerObject* obj, const char* path, SDL_Renderer* screen);
void PlayerObject_Render(PlayerObject* obj, SDL_Renderer* des);
void PlayerObject_HandleInputAction(PlayerObject* obj, SDL_Event events, SDL_Renderer* screen);
void PlayerObject_SetClips(PlayerObject* obj);
void PlayerObject_DoPlayer(PlayerObject* obj, Map* map_data);
void PlayerObject_CheckToMap(PlayerObject* obj, Map* map_data);
void PlayerObject_SetMapXY(PlayerObject* obj, const int map_x, const int map_y);
void PlayerObject_CenterEntityOnMap(PlayerObject* obj, Map* map_data);
void PlayerObject_UpdateImagePlayer(PlayerObject* obj, SDL_Renderer* des);
//void PlayerObject_SetBulletList(PlayerObject* obj, BulletObject** bullet_list);
//BulletObject** PlayerObject_GetBulletList(PlayerObject* obj);
void PlayerObject_HandldeBulle(PlayerObject* obj, SDL_Renderer* des);
void PlayerObject_IncreaseMoney(PlayerObject* obj);

#endif // !PLAYER_OBJECT_H_
