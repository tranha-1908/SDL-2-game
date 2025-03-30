#include"BIRD_OBJECT.h"


BirdObject::BirdObject(){

    is_move=true;
    time = 0;
    velocity_x = 50;
    velocity_y = 50;
    destroy_pig = false;
    destroy_block = false;
    sound2 = Mix_LoadWAV("audio/destroy_pig.wav");
    Mix_VolumeChunk(sound2, MIX_MAX_VOLUME / 3);
}
BirdObject::~BirdObject()
{

}

void BirdObject::HandleMove( Map& map_data)
{

    float x = start_x + velocity_x* time;
    float y = start_y - velocity_y*time +0.5*Gravity*time*time;
    SetRect(x,y);
    if(rect_.x > SCREEN_WIDTH|| (rect_.y)>SCREEN_HEIGHT-92)
        {
            set_is_move(false);
        }
    CheckToMap(map_data);
    set_time(time + step_time);

}

void BirdObject::CheckToMap(Map& map_data)
{
    int x_ = (rect_.x + rect_.w/2-538)/TILE_SIZE;
    int y_ = (rect_.y + rect_.h/2)/TILE_SIZE;

    if(x_>=0 && x_ < MAX_MAP_x && y_>=0 && y_ <MAX_MAP_y &&map_data.tile[y_][x_] != 0 )
    {   for(int x = x_-1; x <= x_+1;x++)
        {
            for(int y = y_-1;y<=y_+1;y++){
                        if(map_data.tile[y][x] == 4){
                            map_data.tile[y][x] = 5;
                        }
                        else if(map_data.tile[y][x] == 5){
                            Mix_PlayChannel(-1, sound2, 0);
                            map_data.tile[y][x] = 0;
                            destroy_pig = true;

                        }
                        else if(map_data.tile[y][x] ==3){
                            map_data.tile[y][x] = 2;

                        }
                        else if(map_data.tile[y][x] ==2){
                            map_data.tile[y][x] = 1;

                        }
                        else if(map_data.tile[y][x] ==1){
                            map_data.tile[y][x] = 0;
                            destroy_block = true;
                        }


            }
        }
        set_is_move(false);
    }

}
void BirdObject::explore(SDL_Renderer*des)
{
    char file_img[30];
    SDL_Rect rect = rect_;
    SetRect(rect.x -rect.w/2,rect.y-rect.h/2);
    for (int i = 1; i <=4; i++) {
        sprintf_s(file_img, "image/expl%d.png", i);
        LoadImg(file_img, des);
        Render(des);
        SDL_RenderPresent(des);
        SDL_Delay(20);
    }
}
