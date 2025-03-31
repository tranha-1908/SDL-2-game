#include"COMMON_FUNC.h"
#include"BASE_OBJECT.h"
#include"BIRD_OBJECT.h"
#include"GAME_MAP.h"
#include"MAIN_OBJECT.h"
#include"TEXT_OBJECT.h"
BaseObject g_game;
MainObject p_player;
MainObject p_mouse;
MainObject button;
MainObject button_close;
MainObject button_mute;
GameMap game_map;
TTF_Font* font_game= NULL;
TextObject Information;
Mix_Chunk *sound1;

bool InitData(){
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
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        success= false;
}
    return success;
}
void ResetGame(){
    g_game.LoadImg("image/background.jpg",g_screen);
    p_player.LoadImg("image/slingshot.png",g_screen);
    game_map.LoadMap("map_.txt");
    game_map.LoadTiles(g_screen);
    button_close.LoadImg("image/close.png",g_screen);
    button_close.SetRect(1000,0);
    button_mute.LoadImg("image/mute.png",g_screen);
    button_mute.SetRect(1060,0);
    p_mouse.LoadImg("image/red.png",g_screen);
    p_player.reset();
    playing = true;
}
bool InGame(){
    g_game.LoadImg("image/ingame.png",g_screen);
    g_game.Render(g_screen);
    g_game.SetRect(458,246);
    if(!g_game.LoadImg("image/play.png",g_screen))
    {
        return false;
    }
    g_game.Render(g_screen);
    SDL_RenderPresent(g_screen);
    music = Mix_LoadMUS("audio/ingame.mp3");
    sound1 = Mix_LoadWAV("audio/shoot.wav");
    Mix_VolumeChunk(sound1, MIX_MAX_VOLUME / 3);
    if (music == NULL) {
        return false;
    }
    Mix_PlayMusic(music, -1);
    volume_on = true;
    SDL_RenderPresent(g_screen);
    g_game.waitMouseButton();
    g_game.SetRect(0,0);
    playing = true;
    Mix_VolumeMusic(MIX_MAX_VOLUME / 4);
    ResetGame();
    Information.SetColor(255,255,255,255);
    return true;

}

void EndGame(bool result, int score){
    if(!playing){
        if(!button.LoadImg("image/result.png",g_screen))
           {
               return ;
           }
        int x = SCREEN_WIDTH/2-350/2;
        int y = SCREEN_HEIGHT/2-350/2;
        button.SetRect(x,y);
        button.Render(g_screen);

        Mix_ResumeMusic();

        std::string text;
        if(result){
            text = "  YOU WIN!";
        }
        else {
            text = "  TRY AGAIN!";
        }
        TextObject text_result;
        text_result.SetColor(255,255,255,255);
        text_result.SetText(text);
        text_result.LoadFromRenderText(font_game,g_screen);
        text_result.RenderText(g_screen,x+100,y+30);
        text = std::to_string(score);
        text_result.SetText(text);
        text_result.LoadFromRenderText(font_game,g_screen);
        text_result.RenderText(g_screen,x+60,y+290);

        button.LoadImg("image/again.png",g_screen);
        button.SetRect(SCREEN_WIDTH/2-25,SCREEN_HEIGHT/2-25);
        button.Render(g_screen);
        SDL_RenderPresent(g_screen);
        button.waitMouseButton();
        playing = true;
    }

}
void close(){
    Mix_FreeChunk(sound1);
    Mix_FreeMusic(music);
    Mix_CloseAudio();
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

    int x,y;
    while(playing)
    {
        while(SDL_PollEvent(&g_event))
        {   SDL_GetMouseState(&x,&y);
            if(g_event.type== SDL_QUIT )
            {
                playing=false;
            }
            else if(g_event.type == SDL_MOUSEBUTTONDOWN&&g_event.button.button == SDL_BUTTON_LEFT){
                        if(button_close.check_button(x,y)){
                            playing = false;
                        }
                        else if(button_mute.check_button(x,y)){
                                if(volume_on){
                                    Mix_PauseMusic();
                                    volume_on = false;
                                    }
                                else {
                                    Mix_ResumeMusic();
                                    volume_on = true;
                                }
                        }
                        else{
                            int delta_x = -x + origin_x;
                            int delta_y = -origin_y + y;

                            BirdObject* bird = new BirdObject;
                            bird->set_start(x,y);
                            bird->set_velocity_x(delta_x);
                            bird->set_velocity_y(delta_y);
                            bird->LoadImg("image/red.png", g_screen);
                            Mix_PlayChannel(-1, sound1, 0);
                            p_player.number_bird -=1;
                            p_player.p_bird_list.push_back(bird);
                            bird = NULL;
                            break;
                        }

                }
                else if(x <SCREEN_WIDTH/2){
                    p_mouse.SetRect(x,y);
                    p_mouse.Render(g_screen);
                    p_mouse.DrawTrajectory(g_screen,x,y);
                    SDL_RenderPresent(g_screen);

                }
            SDL_Delay(30);

        }
        if(p_player.Result_game())
            {
                    playing = false;
                    EndGame(p_player.Result, p_player.score);
                    if(playing){
                        ResetGame();
                    }
            }
        SDL_RenderClear(g_screen);
        g_game.Render(g_screen);
        game_map.DrawMap(g_screen);
        button_close.Render(g_screen);
        button_mute.Render(g_screen);
        p_player.Render(g_screen);
        p_player.HandleBird(g_screen,game_map.game_map_);

        std::string str_val = "Bird:    " + std::to_string(p_player.number_bird)
                               + "    Pig:   " + std::to_string(p_player.number_pig)
                               + "    Score:    " + std::to_string(p_player.score);

        Information.SetText(str_val);
        Information.LoadFromRenderText(font_game,g_screen);
        Information.RenderText(g_screen,0,0);

        SDL_RenderPresent(g_screen);
    }
    close();
    return 1;
}
