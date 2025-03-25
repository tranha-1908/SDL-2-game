#include<fstream>

#include "game_map.h"

void GameMap::LoadMap(char* name)
{
    std::ifstream file(name); // Sử dụng fstream để mở file nhị phân
    if (!file.is_open())
    {
        return;
    }
    game_map_.index_x = 0;
    game_map_.index_y = 0;
    for (int i = 0; i < MAX_MAP_y; i++) {
        for (int j = 0; j < MAX_MAP_x; j++) {
            if (!(file >> game_map_.tile[i][j])) { // Đọc từ fstream
                file.close();
                return; // Xử lý lỗi đọc file
            }
            int val = game_map_.tile[i][j];
            //std::cout << i <<' '<< j << " " << val << std::endl;
            /*if (val > 0) {
                if (j > game_map_.index_x) {
                    game_map_.index_x = j;
                    std::cout << game_map_.index_x;
                }
                if (i > game_map_.index_y) {
                    game_map_.index_y = i;
                }
            }*/
        }
    }

   /* game_map_.index_x = (game_map_.index_x + 1) * TILE_SIZE;
    game_map_.index_y = (game_map_.index_y + 1) * TILE_SIZE;
    game_map_.start_x_ = 0;
    game_map_.start_y_ = 0;*/
    game_map_.filename = name;
    file.close(); // Đóng file
}

void GameMap::LoadTiles(SDL_Renderer* screen)
{
    char file_img[30];
    for (int i = 0; i < MAX_TILES; i++) {
        sprintf_s(file_img, "%d.png", i);
       // std:: cout << file_img<<std:: endl;
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

    for (int i = 0; i < SCREEN_HEIGHT-92; i += TILE_SIZE) {
        map_y = i/ TILE_SIZE;
        for (int j = 338; j < SCREEN_WIDTH; j += TILE_SIZE) {
            map_x = (j-338)/TILE_SIZE;
            int val = game_map_.tile[map_y][map_x];
            if (val > 0) {
                std:: cout << i <<' '<< j << ' '<< val << std:: endl;
                tile_mat[val].SetRect(j, i);
                tile_mat[val].Render(screen);
            }
        }
    }
}
