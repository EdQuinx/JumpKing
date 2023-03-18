#include "PlayerObject.h"

PlayerObject PlayerObject_Create() {

	PlayerObject obj;
	obj.baseObject = BaseObject_Create();
	obj.frame = 0;
	obj.posX = 0;
	obj.posY = 0;
	obj.moveValueX = 0;
	obj.moveValueY = 0;
	obj.frameWidth = 0;
	obj.frameHeight = 0;
	obj.playerStatus = WALK_NONE;
	obj.keyInputType.right = 0;
	obj.keyInputType.left = 0;
	obj.keyInputType.jump = 0;
	obj.keyInputType.down = 0;
	obj.keyInputType.up = 0;
	obj.isOnGround = false;
	obj.mapX = 0;
	obj.mapY = 0;
	obj.frameTime = 0;
	//obj.present_bullet_ = BulletObject_SPHERE_BULLET;
	obj.money_count = 0;

	obj.Destroy = PlayerObject_Destroy;
	obj.LoadImg = PlayerObject_LoadImg;
	obj.Render = PlayerObject_Render;
	obj.HandleInputAction = PlayerObject_HandleInputAction;
	obj.set_clips = PlayerObject_SetClips;
	obj.DoPlayer = PlayerObject_DoPlayer;
	obj.CheckToMap = PlayerObject_CheckToMap;
	obj.SetMapXY = PlayerObject_SetMapXY;
	obj.CenterEntityOnMap = PlayerObject_CenterEntityOnMap;
	obj.UpdateImagePlayer = PlayerObject_UpdateImagePlayer;
	return obj;
}

void PlayerObject_Destroy(PlayerObject* obj) {
	if (obj) {
		/*if (main_object->p_bullet_list) {
			for (int i = 0; i < main_object->bullet_list_size; i++) {
				BulletObject_Destroy(main_object->p_bullet_list[i]);
			}
			free(main_object->p_bullet_list);
		}*/
		obj->baseObject.Free(&obj->baseObject);
		obj->baseObject.Destroy(&obj->baseObject);
		free(obj);
	}
}

void PlayerObject_SetMapXY(PlayerObject* obj, const int map_x, const int map_y)
{
	obj->mapX = map_x;
	obj->mapY = map_y;
}

bool PlayerObject_LoadImg(PlayerObject* obj, const char* path, SDL_Renderer* screen) {
    bool ret = obj->baseObject.LoadImg(&(obj->baseObject), path, screen);
    obj->baseObject.objectRect.x;


    if (ret == true) {
        obj->frameWidth = obj->baseObject.objectRect.w / 8;
        obj->frameHeight = obj->baseObject.objectRect.h;
    }
    return ret;
}

void PlayerObject_SetClips(PlayerObject* obj)
{
	if (obj->frameWidth > 0 && obj->frameHeight > 0)
	{
		for (int i = 0; i < 8; i++)
		{
			obj->frameSprites[i].x = i * obj->frameWidth;
			obj->frameSprites[i].y = 0;
			obj->frameSprites[i].w = obj->frameWidth;
			obj->frameSprites[i].h = obj->frameHeight;
		}
	}
}

void PlayerObject_Render(PlayerObject* obj, SDL_Renderer* des) {
	obj->UpdateImagePlayer(obj, des);
	if (obj->keyInputType.left == 1 ||
		obj->keyInputType.right == 1) {
		obj->frame++;
	}
	else {
		obj->frame = 0;
	}

	if (obj->frame >= 8) {
		obj->frame = 0;
	}

	if (obj->frameTime == 0) {
		obj->baseObject.objectRect.x = obj->posX - obj->mapX;
		obj->baseObject.objectRect.y = obj->posY - obj->mapY;

		SDL_Rect* current_clip = &obj->frameSprites[obj->frame];

		SDL_Rect quadRect = { obj->baseObject.objectRect.x, obj->baseObject.objectRect.y , 
			obj->frameWidth, obj->frameHeight };

		SDL_RenderCopy(des, obj->baseObject.object, current_clip, &quadRect);
	}
}

void PlayerObject_HandleInputAction(PlayerObject* obj, SDL_Event events, SDL_Renderer* screen) {
	if (events.type == SDL_KEYDOWN) {
		switch (events.key.keysym.sym)
		{
		case SDLK_d:
			obj->playerStatus = WALK_RIGHT;
			obj->keyInputType.right = 1;
			obj->keyInputType.left = 0;
			break;
		case SDLK_a:
			obj->playerStatus = WALK_LEFT;
			obj->keyInputType.left = 1;
			obj->keyInputType.right = 0;
		case SDLK_1:
			//obj->present_bullet_ = BulletObject::SPHERE_BULLET;
			break;
		case SDLK_2:
			//present_bullet_ = BulletObject::LASER_BULLET;
			break;
		case SDLK_w:
			obj->keyInputType.jump = 1;
			break;
		default:
			break;
		}
	}
	else if (events.type == SDL_KEYUP) {
		switch (events.key.keysym.sym)
		{
		case SDLK_d:
			obj->keyInputType.right = 0;
			break;
		case SDLK_a:
			obj->keyInputType.left = 0;
			break;
		case SDLK_w:
			obj->keyInputType.jump = 0;
			break;
		default:
			break;
		}
	}
	//if (events.type == SDL_KEYDOWN) {
	//	if (events.) {
	//		obj->keyInputType.jump_ = 1;
	//	}
	//	//else if (events.button.button == SDL_BUTTON_LEFT) {
	//	//	BulletObject* p_bullet = new BulletObject();
	//	//	p_bullet->set_bulet_type(present_bullet_);
	//	//	p_bullet->LoadImgBullet(screen);
	//	//	if (playerStatus == WALK_LEFT) {
	//	//		p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
	//	//		p_bullet->SetRect(this->objectRect.x, this->objectRect.y + frameHeight * 0.25);
	//	//	}
	//	//	else if (playerStatus == WALK_RIGHT) {
	//	//		p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT);
	//	//		p_bullet->SetRect(this->objectRect.x + frameWidth - 20, this->objectRect.y + frameHeight * 0.3);
	//	//	}
	//	//	p_bullet->set_x_val(20);
	//	//	p_bullet->set_y_val(20);
	//	//	p_bullet->set_is_move(true);
	//	//	p_bullet_list_.push_back(p_bullet);
	//	//}
	//}
}

//void PlayerObject_HandldeBulle(PlayerObject* obj, SDL_Renderer* des) {
//	for (size_t i = 0; i < obj->p_bullet_list_.size(); i++)
//	{
//		BulletObject* p_bullet = p_bullet_list_.at(i);
//		if (p_bullet != NULL) {
//			if (p_bullet->get_is_move() == true) {
//				p_bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
//				p_bullet->Render(des);
//			}
//			else {
//				p_bullet_list_.erase(p_bullet_list_.begin() + i);
//				if (p_bullet != NULL) {
//					delete p_bullet;
//					p_bullet = NULL;
//				}
//			}
//		}
//	}
//}

void PlayerObject_DoPlayer(PlayerObject* obj, Map* map_data) {
	if (obj->frameTime == 0) {
		obj->moveValueX = 0;
		obj->moveValueY += (GRAVITY_SPEED);

		if (obj->moveValueY >= MAX_FALL_SPEED) {
			obj->moveValueY = MAX_FALL_SPEED;
		}

		if (obj->keyInputType.left == 1) {
			obj->moveValueX -= PLAYER_SPEED;
		}
		else if (obj->keyInputType.right == 1) {
			obj->moveValueX += PLAYER_SPEED;
		}

		if (obj->keyInputType.jump == 1) {
			if (obj->isOnGround == true) {
				obj->moveValueY = -PLAYER_JUMP_VAL;
				obj->isOnGround = false;
			}
			obj->keyInputType.jump = 0;
		}

		obj->CheckToMap(obj, map_data);
		obj->CenterEntityOnMap(obj, map_data);
	}
	if (obj->frameTime > 0) {
		obj->frameTime--;
		if (obj->frameTime == 0) {
			obj->isOnGround = false;
			if (obj->posX > 256) {
				obj->posX -= 256;
			}
			else {
				obj->posX = 0;
			}
			obj->posY = 0;
			obj->moveValueX = 0;
			obj->moveValueY = 0;
		}
	}
}

void PlayerObject_CenterEntityOnMap(PlayerObject* obj, Map* map_data) {
	map_data->startX = obj->posX - (SCREEN_WIDTH / 2);
	if (map_data->startX < 0) {
		map_data->startX = 0;
	}
	else if (map_data->startX + SCREEN_WIDTH >= map_data->maxX) {
		map_data->startX = map_data->maxX - SCREEN_WIDTH;
	}

	map_data->startY = obj->posY - (SCREEN_HEIGHT / 2);
	if (map_data->startY < 0) {
		map_data->startY = 0;
	}
	else if (map_data->startY + SCREEN_HEIGHT >= map_data->maxY) {
		map_data->startY = map_data->maxY - SCREEN_HEIGHT;
	}
}

void PlayerObject_CheckToMap(PlayerObject* obj, Map* map_data) {
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	//Check horizontial 
	int height_min = obj->frameHeight < TILE_SIZE ? obj->frameHeight : TILE_SIZE;

	x1 = (obj->posX + obj->moveValueX) / TILE_SIZE;
	x2 = (obj->posX + obj->moveValueX + obj->frameWidth - 1) / TILE_SIZE;

	y1 = (obj->posY) / TILE_SIZE;
	y2 = (obj->posY + height_min - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y) {
		if (obj->moveValueX > 0) {

			int val1 = map_data->tile[y1][x2];
			int val2 = map_data->tile[y2][x2];

			if (val1 == STATE_MONEY || val2 == STATE_MONEY) {
				map_data->tile[y1][x2] = 0;
				map_data->tile[y2][x2] = 0;
				PlayerObject_IncreaseMoney(obj);
			}
			else {
				if (val1 != BLANK_TILE || val2 != BLANK_TILE) {
					obj->posX = x2 * TILE_SIZE;
					obj->posX -= obj->frameWidth + 1;
					obj->moveValueX = 0;
				}
			}
		}
		else if (obj->moveValueX < 0) {
			int val1 = map_data->tile[y1][x1];
			int val2 = map_data->tile[y2][x1];

			if (val1 == STATE_MONEY || val2 == STATE_MONEY) {
				map_data->tile[y1][x1] = 0;
				map_data->tile[y2][x1] = 0;
				PlayerObject_IncreaseMoney(obj);
			}

			else {
				if (val1 != BLANK_TILE || val2 != BLANK_TILE) {
					obj->posX = (x1 + 1) * TILE_SIZE;
					obj->moveValueX = 0;
				}
			}

		}
	}

	//Check vartical
	int width_min = obj->frameWidth < TILE_SIZE ? obj->frameWidth : TILE_SIZE;
	x1 = (obj->posX) / TILE_SIZE;
	x2 = (obj->posX + width_min) / TILE_SIZE;

	y1 = (obj->posY + obj->moveValueY) / TILE_SIZE;
	y2 = (obj->posY + obj->moveValueY + obj->frameHeight - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		if (obj->moveValueY > 0) {
			int val1 = map_data->tile[y2][x1];
			int val2 = map_data->tile[y2][x2];

			if (val1 == STATE_MONEY || val2 == STATE_MONEY) {
				map_data->tile[y2][x1] = 0;
				map_data->tile[y2][x2] = 0;
				PlayerObject_IncreaseMoney(obj);
			}
			else if (val1 != BLANK_TILE || val2 != BLANK_TILE) {
				obj->posY = y2 * TILE_SIZE;
				obj->posY -= obj->frameHeight + 1;
				obj->moveValueY = 0;
				obj->isOnGround = true;

				if (obj->playerStatus == WALK_NONE) {
					obj->playerStatus = WALK_RIGHT;
				}
			}
		}
		else if (obj->moveValueY < 0) {
			int val1 = map_data->tile[y1][x1];
			int val2 = map_data->tile[y1][x2];

			if (val1 == STATE_MONEY || val2 == STATE_MONEY) {
				map_data->tile[y1][x1] = 0;
				map_data->tile[y1][x2] = 0;
				PlayerObject_IncreaseMoney(obj);
			}
			else if (val1 != BLANK_TILE || val2 != BLANK_TILE) {
				obj->posY = (y1 + 1) * TILE_SIZE;
				obj->moveValueY = 0;
			}
		}
	}


	obj->posX += obj->moveValueX;
	obj->posY += obj->moveValueY;

	if (obj->posX < 0) {
		obj->posX = 0;
	}
	else if (obj->posX + obj->frameWidth > map_data->maxX) {
		obj->posX = map_data->maxX - obj->frameWidth - 1;
	}

	if (obj->posY > map_data->maxY) {
		obj->frameTime = 60;
	}
}

void PlayerObject_IncreaseMoney(PlayerObject* obj) {
	obj->money_count++;
}

void PlayerObject_UpdateImagePlayer(PlayerObject* obj, SDL_Renderer* des) {
	if (obj->isOnGround) {
		if (obj->playerStatus == WALK_LEFT) {
			obj->baseObject.LoadImg(&obj->baseObject, "img/player sprite/player_left.png", des);
		}
		else {
			obj->baseObject.LoadImg(&obj->baseObject, "img/player sprite/player_right.png", des);
		}
	}
	else {
		if (obj->playerStatus == WALK_LEFT) {
			obj->baseObject.LoadImg(&obj->baseObject, "img/player sprite/jum_left.png", des);
		}
		else {
			obj->baseObject.LoadImg(&obj->baseObject, "img/player sprite/jum_right.png", des);
		}
	}
}
