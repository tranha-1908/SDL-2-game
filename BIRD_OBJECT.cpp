#include"BIRD_OBJECT.h"


BirdObject::BirdObject(){
    rect_.x = start_x;
    rect_.y = start_y;
    is_move=false;
    type_bird = 1;
}
BirdObject::~BirdObject()
{

}





void BirdObject:: HandleBird(SDL_Renderer* des)
{
    for(int i = 0;i<p_bird_list.size();i++)
    {
        BirdObject* p_bird = p_bird_list.at(i);
        if(p_bird != NULL)
            {
                if(p_bird->get_is_move()==true)
                {
                    p_bird->HandleMove(SCREEN_WIDTH,SCREEN_HEIGHT);
                    p_bird->Render_bird(des);
                }
                else p_bird_list.erase(p_bird_list.begin()+i);
                if(p_bird!=NULL)
                {
                    delete p_bird;
                    p_bird = NULL;
                }
            }
    }
}

void BirdObject::CheckToMap(Map& map_data)
{
    int x = 0;
    int y = 0;

    x = (rect_.x+rect_.w)/TILE_SIZE;
    y = (rect_.y+rect_.h)/TILE_SIZE;
    if(x>=0 && x< MAX_MAP_x && y>=0 && y< MAX_MAP_y)
    {
        if(map_data.tile[x][y] != 0)
        {
            set_is_move(false);
        }
    }
}

