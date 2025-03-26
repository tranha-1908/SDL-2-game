#include"BIRD_OBJECT.h"


BirdObject::BirdObject(){
    rect_.x = start_x;
    rect_.y = start_y;
    is_move=true;
    time = 0;
    type_bird = 1;
    angle = 0;
    velocity =100;
    destroy_block= false;
    destroy_pig = false;
}
BirdObject::~BirdObject()
{

}

void BirdObject::HandleMove(const int& x_border, const int& y_border, Map& map_data)
{

    float x = start_x + get_x_veloc()* time;
    float y = start_y + get_y_veloc()*time +0.5*Gravity*time*time;
    SetRect(x,y);
    if(rect_.x > x_border|| rect_.y>y_border-92)
        {
            set_is_move(false);
        }
    CheckToMap(map_data);
    set_time(time + step_time);

}
void BirdObject::CheckToMap(Map& map_data)
{
    int x = (rect_.x+rect_.w-338)/TILE_SIZE;
    int y = (rect_.y)/TILE_SIZE;

    if(x> MAX_MAP_x || y<0 || y> MAX_MAP_y )
    {
        set_is_move(false);
    }
    else {
        if(x>=0 && map_data.tile[y][x] != 0 )
        {


            if(map_data.tile[y][x] == 4){
                destroy_pig = true;

            }
            if(map_data.tile[y][x]>=1 || map_data.tile[y][x] <=3){
                destroy_block = true;
            }

            map_data.tile[y][x] = 0 ;
            set_is_move(false);
        }

    }
}
