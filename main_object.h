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
    void set_bird_list(std::vector<BirdObject*> bird_list)
    {
        p_bird_list = bird_list;

    }
    std:: vector<BirdObject*> get_bird_list() const
    {
        return p_bird_list;
    }

    bool Result_game();
    std::vector<BirdObject*> p_bird_list;
    int score = 0;
    int number_bird = 10;
    int number_pig = 2;
    bool Result;
};
#endif // MAIN_OBJECT_H
