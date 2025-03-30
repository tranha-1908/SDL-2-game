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

    void HandleBird(SDL_Renderer* des, Map& map_data);
    bool Result_game();
    void reset();
    void DrawTrajectory(SDL_Renderer* renderer, int start_x, int start_y);
    bool check_button(const int&x, const int& y);
    std::vector<BirdObject*> p_bird_list;

    int score = 0;
    int number_bird = 20;
    int number_pig = 7;
    bool Result;
};
#endif // MAIN_OBJECT_H
