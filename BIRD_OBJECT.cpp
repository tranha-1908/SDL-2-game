#include"BIRD_OBJECT.h"


BirdObject::BirdObject(){
    rect_.x = start_x;
    rect_.y = start_y;
    is_move=true;
    time = 0;
    type_bird = 1;
    angle = 0;
    velocity =100;
}
BirdObject::~BirdObject()
{

}

void BirdObject::HandleMove(const int& x_border, const int& y_border, Map& map_data)
{

    float x = start_x + get_x_veloc()* time;
    float y = start_y + get_y_veloc()*time +0.5*Gravity*time*time;
    SetRect(x,y);
    if(rect_.x > x_border|| rect_.y>y_border)
        {
            set_is_move(false);
        }
    CheckToMap(map_data);
    set_time(time + step_time);

}
void BirdObject::CheckToMap(Map& map_data)
{
    int y = (rect_.x-338-1)/TILE_SIZE;
    int x = (rect_.y-1)/TILE_SIZE;
    std::cout << x << " & " << y << '\n';
    if(x>=0 && x< MAX_MAP_x && y>=0 && y< MAX_MAP_y)
    {
        if(map_data.tile[x][y] != 0)
        {
            set_is_move(false);
        }
    }
}
