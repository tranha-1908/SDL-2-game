#include<fstream>

#include "game_map.h"

void GameMap::LoadMap(char* name)
{
    std::ifstream file(name);
    if (!file.is_open())
    {
        return;
    }
    game_map_.index_x = 0;
    game_map_.index_y = 0;
    for (int i = 0; i < MAX_MAP_y; ++i) {
        for (int j = 0; j < MAX_MAP_x; ++j) {
            if (!(file >> game_map_.tile[i][j])) {
                file.close();
                return;
            }
            int val = game_map_.tile[i][j];

        }
    }


    game_map_.filename = name;
    file.close();
}

void GameMap::LoadTiles(SDL_Renderer* screen)
{
    char file_img[30];
    for (int i = 0; i < MAX_TILES; i++) {
        sprintf_s(file_img, "map/%d.png", i);

        std::ifstream file(file_img);
        if (!file.is_open()) {
            continue;
        }
        file.close();
        tile_mat[i].LoadImg(file_img, screen);

    }
}
void GameMap::DrawMap(SDL_Renderer* screen)
{
    int map_x = 0;
    int map_y = 0;

    for (int i = 10; i < SCREEN_HEIGHT-90; i += TILE_SIZE) {
        map_y = (i+10)/ TILE_SIZE;
        for (int j = 568; j < SCREEN_WIDTH; j += TILE_SIZE) {
            map_x = (j-568)/TILE_SIZE;
            int val = game_map_.tile[map_y][map_x];
            if (val > 0) {
                    tile_mat[val].SetRect(j, i);
                    tile_mat[val].Render(screen);

            }
        }
    }
}


