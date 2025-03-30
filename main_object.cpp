#include"main_object.h"

MainObject::MainObject()
{
    rect_.x = origin_x-20;
    rect_.y = origin_y;


}
MainObject::~MainObject()
{

}

void MainObject:: HandleBird(SDL_Renderer* des, Map& map_data)
{
    for(int i = 0;i<(int)p_bird_list.size();i++)
    {
        BirdObject* p_bird = p_bird_list.at(i);
        if(p_bird != NULL)
            {

                if(p_bird->get_is_move()==true)
                {
                    p_bird->HandleMove(map_data);
                    p_bird->Render(des);
                    if(p_bird->get_is_move()==false){
                        p_bird->explore(des);
                    }
                    if(p_bird->destroy_block){
                        score += 1000;
                    }
                    if(p_bird->destroy_pig){
                        score += 5000;
                        number_pig -=1;

                    }
                }
                else {p_bird_list.erase(p_bird_list.begin()+i);
                    if(p_bird!=NULL)
                    {
                        delete p_bird;
                        p_bird = NULL;
                    }
                }
            }
    }
}
void MainObject::reset()
{
    score = 0;
    number_bird = 20;
    number_pig = 7;
    Result = false;
    p_bird_list.clear();
}

bool MainObject::Result_game()
{
    if(number_bird < 0 && number_pig != 0){
        Result = false;
        return true;
    }
    if(number_pig ==0 && number_bird != 0){
        Result = true;
        return true;
    }
    return false;
}
void MainObject::DrawTrajectory(SDL_Renderer* renderer, int start_x, int start_y) {

    const int num_points = 30 ;
    float time = 0;
    SDL_SetRenderDrawColor(renderer, 0   , 0  , 0  , 255 );
    for(int i = 0; i < num_points;i++){
        int x = start_x + (-start_x + origin_x)* time;
        int y = start_y - (-origin_y + start_y)*time + 0.5*Gravity*time*time;
        SDL_Rect square = { x , y , 5 , 5  };
        SDL_RenderFillRect(renderer, &square);
        time += 0.5 ;
    }
}
bool MainObject::check_button(const int&x, const int& y){
    if(x >= rect_.x && x <= rect_.x + rect_.w && y >= rect_.y && y <= rect_.y+rect_.h)
    {
        return true;
    }
    else return false;
}

