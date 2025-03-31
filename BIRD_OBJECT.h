#ifndef BIRD_OBJECT_H
#define BIRD_OBJECT_H
#include "COMMON_FUNC.h"
#include"BASE_OBJECT.h"



#define step_time 0.02
class BirdObject:public BaseObject
{
public:
    BirdObject();
    ~BirdObject();

    bool destroy_pig;
    bool destroy_block1,destroy_block2,destroy_block3;
    void set_velocity_x(const float& velocity_){ velocity_x = velocity_;}
    void set_velocity_y(const float& velocity_){ velocity_y = velocity_;}
    void set_time(const float& time_){time = time_;}
    void set_start(const int& x, const int& y){ start_x = x; start_y = y;}

    void set_is_move(const bool& isMove) { is_move = isMove;}
    bool get_is_move() const {return is_move;}

    void HandleMove(Map& map_data);
    void CheckToMap(Map& map_data);

    void explore(SDL_Renderer* des);



    bool is_move;
    int start_x;
    int start_y;
    float velocity_x;
    float velocity_y;
    float time;
    Mix_Chunk *sound2;

};
#endif // MAIN_OBJECT_H
