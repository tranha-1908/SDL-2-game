#include"main_object.h"

MainObject::MainObject()
{
    rect_.x = 40;
    rect_.y = 380;
    velocity = 100;
    angle = 0;
}
MainObject::~MainObject()
{

}
void MainObject::HandleInput(SDL_Event events, SDL_Renderer* screen){

    if(events.type == SDL_KEYDOWN)
    {
        switch(events.key.keysym.sym)
        {
        case SDLK_RIGHT:
            {
                set_angle(angle-5);
                break;
            }
        case SDLK_LEFT:
            {
                set_angle(angle+5);
                break;
            }
        case SDLK_UP:
            {
                set_velocity(velocity+10);
                break;
            }
        case SDLK_DOWN:
            {
                set_velocity(velocity-10);
                break;
            }
        default:
            break;
        }
    }

    if(events.type == SDL_MOUSEBUTTONDOWN){
       if(events.button.button == SDL_BUTTON_LEFT)
        {
            BirdObject* p_bird = new BirdObject();
            p_bird->LoadImg_bird("image/red.png",screen);
            p_bird->SetRect_bird(40,200);
            p_bird->set_angle(angle_);
            p_bird->set_velocity(velocity_);
            p_bird->p_bird_list.push_back(p_bird);
        }
    }
}
void MainObject::HandleMove(const int& x_border, const int& y_border)
{
    float time = 0;
    rect_.x = start_x + get_x_veloc()* time;
    rect_.y = start_y + get_x_veloc()*time +0.5*Gravity*time*time;
    if(rect_.x > x_border|| rect_.y>y_border)
        {
            is_move = false;
        }

}
