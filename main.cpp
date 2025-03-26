#include"COMMON_FUNC.h"
#include"BASE_OBJECT.h"
#include"game_map.h"
#include "BIRD_OBJECT.h"
#include"main_object.h"
#include"TextObject.h"
BaseObject g_game;
TTF_Font* font_game= NULL;
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
    if(TTF_Init()==-1)
    {
        success = false;
    }
    font_game = TTF_OpenFont("font.ttf",30 );
    if(font_game == NULL){
        success = false;
    }

    return success;
}
bool InGame()
{
    if(!g_game.LoadImg("image/ingame.png",g_screen))
    {
        return false;
    }
    g_game.Render(g_screen,NULL);
    g_game.SetRect(458,246);
    if(!g_game.LoadImg("image/play.png",g_screen))
    {
        return false;
    }
    g_game.Render(g_screen,NULL);
    SDL_RenderPresent(g_screen);
    g_game.SetRect(0,0);
    return true;

}

bool LoadBackground()
{
    if(!g_game.LoadImg("image/background.jpg",g_screen))
    {
        return false;
    }
    return true;
}
void EndGame(bool result){
    if(!playing){
        if(!g_game.LoadImg("image/result.png",g_screen))
           {
               return ;
           }
           int x = SCREEN_WIDTH/2-350/2;
           int y = SCREEN_HEIGHT/2-350/2;
        g_game.SetRect(x,y);
        g_game.Render(g_screen,NULL);
        std::string text;
        if(result){
            text = "  YOU WIN!";
        }
        else {
            text = "  TRY AGAIN!";
        }
        TextObject text_result;
        text_result.SetColor(255,255,255);
        text_result.SetText(text);
        text_result.LoadFromRenderText(font_game,g_screen);
        text_result.RenderText(g_screen,x+70,y+30);

        SDL_RenderPresent(g_screen);
    }

}
void close()
{
    g_game.free();
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
    if(InGame() == false){
        return -1;
    }
    g_game.waitMouseButton();
    playing = true;

    if(LoadBackground()== false ){
        return -1;
    }

    GameMap game_map;
    game_map.LoadMap("map01.txt");
    game_map.LoadTiles(g_screen);

    MainObject p_player;
    p_player.LoadImg("image/113160.png",g_screen);

    TextObject Information;
    Information.SetColor(255,255,255);

    bool is_quit = false;
    int angle_= 40;
    int velocity_ = 30;
    while(!is_quit&& playing)
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
                        {angle_-=1;
                        break;}
                    case SDLK_LEFT:
                        {angle_+=1;
                        break;}
                    case SDLK_UP:
                        {velocity_+=1;
                        break;}
                    case SDLK_DOWN:
                        {velocity_-=1;
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
                    p_player.number_bird -=1;
                }
            }
        }
        SDL_RenderClear(g_screen);

        g_game.Render(g_screen,NULL);

        game_map.DrawMap(g_screen);
        p_player.Render(g_screen,NULL);

        p_player.HandleBird(g_screen,game_map.game_map_);
        if(p_player.Result_game())
        {
                playing = false;
                break;
        }

        std::string str_val = "Bird:    " + std::to_string(p_player.number_bird)
                               + "    Pig:   " + std::to_string(p_player.number_pig)
                               + "    Score:    " + std::to_string(p_player.score);

        Information.SetText(str_val);
        Information.LoadFromRenderText(font_game,g_screen);
        Information.RenderText(g_screen,0,0);

        SDL_RenderPresent(g_screen);
    }
    EndGame(p_player.Result);
    g_game.waitUntilKeyPress();
    close();
    return 1;
}
