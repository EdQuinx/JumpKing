#include "GameMap.h"

GameMap GameMap_Create()
{
    GameMap obj;
    for (int i = 0; i < MAX_TILES; i++) {
        obj.tileMat[i].baseObject = BaseObject_Create();
    }
    obj.LoadMap = GameMap_LoadMap;
    obj.LoadTiles = GameMap_LoadTiles;
    obj.DrawMap = GameMap_DrawMap;

    obj.GetMap = GameMap_GetMap;
    obj.SetMap = GameMap_SetMap; 
    return obj;
}

void GameMap_Destroy(GameMap* obj)
{
    if (obj) {
        if (obj->tileMat) {
            for (int i = 0; i < MAX_TILES; i++) {
                obj->tileMat[i].baseObject.Destroy(&obj->tileMat[i].baseObject);

            }
        }
        free(obj);
    }
}

Map GameMap_GetMap(GameMap* obj) { return obj->gameMap; }
void GameMap_SetMap(GameMap* obj, const Map* gMap) { obj->gameMap = *gMap; }

void GameMap_LoadMap(GameMap* obj, char* name) {
    FILE* fp = NULL;
    fopen_s(&fp, name, "rb");
    if (fp == NULL) {
        return;
    }

    obj->gameMap.maxX = 0;
    obj->gameMap.maxY = 0;
    for (int i = 0; i < MAX_MAP_Y; i++) {
        for (int j = 0; j < MAX_MAP_X; j++) {
            fscanf_s(fp, "%d", &obj->gameMap.tile[i][j]);
            int val = obj->gameMap.tile[i][j];
            if (val > 0) {
                if (j > obj->gameMap.maxX) {
                    obj->gameMap.maxX = j;
                }
                if (i > obj->gameMap.maxY) {
                    obj->gameMap.maxY = i;
                }
            }
        }
    }
    obj->gameMap.maxX = (obj->gameMap.maxX + 1) * TILE_SIZE;
    obj->gameMap.maxY = (obj->gameMap.maxY + 1) * TILE_SIZE;

    obj->gameMap.startX = 0;
    obj->gameMap.startY = 0;

    obj->gameMap.fileName = name;
    fclose(fp);
}

void GameMap_LoadTiles(GameMap* obj, SDL_Renderer* screen) {
    char file_img[30];
    FILE* fp = NULL;

    for (int i = 0; i < MAX_TILES; i++) {
        sprintf(file_img, "map/%d.png", i);

        fopen_s(&fp, file_img, "rb");
        if (fp == NULL) {
            continue;
        }
        fclose(fp);
        obj->tileMat[i].baseObject.LoadImg(&obj->tileMat[i].baseObject,file_img, screen);
    }
}

void GameMap_DrawMap(GameMap* obj, SDL_Renderer* des) {
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    int map_x = 0;
    int map_y = 0;

    map_x = obj->gameMap.startX / TILE_SIZE;
    x1 = (obj->gameMap.startX % TILE_SIZE) * -1;
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

    map_y = obj->gameMap.startY / TILE_SIZE;
    y1 = (obj->gameMap.startY % TILE_SIZE) * -1;
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

    for (int i = y1; i < y2; i++, i += TILE_SIZE) {
        map_x = obj->gameMap.startX / TILE_SIZE;
        for (int j = x1; j < x2; j += TILE_SIZE) {
            int val = obj->gameMap.tile[map_y][map_x];
            if (val > 0) {
                obj->tileMat[val].baseObject.SetRect(&obj->tileMat[val].baseObject, j, i);
                obj->tileMat[val].baseObject.Render(&obj->tileMat[val].baseObject, des, NULL);
            }
            map_x++;
        }
        map_y++;
    }
}