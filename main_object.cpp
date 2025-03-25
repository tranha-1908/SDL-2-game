#include"main_object.h"

MainObject::MainObject()
{
    rect_.x = 40;
    rect_.y = 380;


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
                    p_bird->HandleMove(SCREEN_WIDTH,SCREEN_HEIGHT, map_data);

                    p_bird->Render(des);
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

