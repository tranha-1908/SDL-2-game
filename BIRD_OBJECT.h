#ifndef BIRD_OBJECT_H
#define BIRD_OBJECT_H
#include "COMMON_FUNC.h"
#include"BASE_OBJECT.h"

#define Gravity 0.98
#define start_x 40
#define start_y 400
#define step_time 0.01
class BirdObject:public BaseObject
{
public:
    BirdObject();
    ~BirdObject();

    bool destroy_pig;
    bool destroy_block;

    void set_angle(const int& angle_){angle = angle_;}
    void set_velocity(const int& velocity_){ velocity = velocity_;}
    void set_time(const float& time_){time = time_;}
    float get_angle_radian () const {return angle*M_PI/180;}
    float get_x_veloc() const {
        float angle_r = get_angle_radian();
        return velocity*cos(angle_r);
    }
    float get_y_veloc() const {
        float angle_r = get_angle_radian();
        return -velocity*sin(angle_r);
    }

    void set_is_move(const bool& isMove) { is_move = isMove;}
    bool get_is_move() const {return is_move;}

    void HandleMove(const int &x_border, const int& y_border, Map& map_data);


    void CheckToMap(Map& map_data);
protected:

    bool is_move;
    int type_bird;
    int velocity;
    int angle ;
    float time;

};
#endif // MAIN_OBJECT_H
