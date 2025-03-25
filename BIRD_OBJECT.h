#ifndef BIRD_OBJECT_H
#define BIRD_OBJECT_H
#include "COMMON_FUNC.h"
#include"BASE_OBJECT.h"

#define Gravity 98
#define start_x 40;
#define start_y 200;
class BirdObject:public BaseObject
{
public:
    BirdObject();
    ~BirdObject();

    /*void LoadImg_bird(const char* filename, SDL_Renderer* screen);
    void SetRect_bird(const int& x, const int& y){rect_bird.x = x; rect_bird.y = y;}
    void Render_bird(SDL_Renderer* des);*/

    void set_is_move(const bool& isMove) { is_move = isMove;}
    bool get_is_move() const {return is_move;}





    void HandleBird(SDL_Renderer* des);
    void set_bird_list(std::vector<BirdObject*> bird_list)
    {
        p_bird_list = bird_list;
    }
    std:: vector<BirdObject*> get_bird_list() const
    {
        return p_bird_list;
    }
    void CheckToMap(Map& map_data);
private:
    bool is_move;
    int type_bird;
    std::vector<BirdObject*> p_bird_list;

};

#endif // MAIN_OBJECT_H
