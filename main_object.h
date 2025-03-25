#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H
#include "COMMON_FUNC.h"
#include "BASE_OBJECT.h"
#include "BIRD_OBJECT.h"
class MainObject: public BaseObject
{
public:
    MainObject();
    ~MainObject();

    void set_angle(const int& angle_){angle = angle_;}
    void set_velocity(const int& vel){ velocity = vel;}

    float get_angle_radian () const {return angle*M_PI/180;}
    float get_x_veloc() const {
        float angle_r = get_angle_radian();
        return velocity*cos(angle_r);
    }
    float get_y_veloc() const {
        float angle_r = get_angle_radian();
        return -velocity*sin(angle_r);
    }

    void HandleInput(SDL_Event events, SDL_Renderer* screen);
    void HandleMove(const int &x_border, const int& y_border);

private:

    int velocity;
    int angle ;
};
#endif // MAIN_OBJECT_H
