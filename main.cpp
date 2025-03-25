#include"COMMON_FUNC.h"
#include"BASE_OBJECT.h"
#include"game_map.h"
#include "BIRD_OBJECT.h"
#include"main_object.h"
BaseObject g_background;
bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if(ret < 0){ success= false;}

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");

    g_window = SDL_CreateWindow("Game_SDL2", SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    if(g_window == NULL){success= false;}
    else
    {
        g_screen= SDL_CreateRenderer(g_window,-1,SDL_RENDERER_ACCELERATED);
        if(g_screen ==NULL){ success = false;}
        else
        {
            int imgflag = IMG_INIT_PNG;
            if(!IMG_Init(imgflag) && imgflag){
                success = false;
            }
        }
    }

    return success;
}


bool LoadBackground()
{
    bool ret = g_background.LoadImg("image/background.jpg",g_screen);
    if(ret == false){
        return false;
    }
    return true;
}
void close()
{
    g_background.free();
    SDL_DestroyRenderer(g_screen);
    g_screen=NULL;
    SDL_DestroyWindow(g_window);
    g_window=NULL;
    IMG_Quit();
    SDL_Quit();
}
int main(int argc, char *argv[])
{

    if(InitData()== false){
        return -1;
    }
    if(LoadBackground()== false ){
        return -1;
    }

    GameMap game_map;
    game_map.LoadMap("map01.txt");
    game_map.LoadTiles(g_screen);

    MainObject p_player;
    p_player.LoadImg("image/113160.png",g_screen);

    bool is_quit = false;
    int angle_= 40;
    int velocity_ = 30;
    while(!is_quit)
    {

        while(SDL_PollEvent(&g_event))
        {

            if(g_event.type== SDL_QUIT)
            {
                is_quit=true;
            }
            if (g_event.type == SDL_KEYDOWN ) {
                switch (g_event.key.keysym.sym) {

                    case SDLK_RIGHT:
                        {angle_-=5;
                        break;}
                    case SDLK_LEFT:
                        {angle_+=5;
                        break;}
                    case SDLK_UP:
                        {velocity_+=5;
                        break;}
                    case SDLK_DOWN:
                        {velocity_-=5;
                        break;}
                    default:
                        break;
                }
                std::cout << angle_ << " & " <<velocity_ << std::endl;
            }
            if(g_event.type == SDL_MOUSEBUTTONDOWN){

                if(g_event.button.button==SDL_BUTTON_LEFT){

                    BirdObject* p_bird = new BirdObject;
                    p_bird->set_angle(angle_);
                    p_bird->set_velocity(velocity_);
                    p_bird->LoadImg("image/red.png", g_screen);
                    p_player.p_bird_list.push_back(p_bird);
                }
            }
        }

        SDL_RenderClear(g_screen);

        g_background.Render(g_screen,NULL);

        game_map.DrawMap(g_screen);
        p_player.Render(g_screen,NULL);
        Map map_data = game_map.get_map();
        p_player.HandleBird(g_screen,map_data);

        SDL_RenderPresent(g_screen);
    }
    close();
    return 1;
}
