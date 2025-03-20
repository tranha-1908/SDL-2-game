#ifndef _GAME__H
#define _GRAME__H
#define RED 1
#define BLUE 2
#define BLACK 3
#include<vector>
using namespace std;
const char* WINDOW_TITLE = "angry_bird";
const int scr_height = 640;
const int scr_width = 1200;
const int tile_size = 40;

SDL_Texture *loadTexture(SDL_Renderer* renderer,const char *filename) //ham tao texture
    {
        //SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

        SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
        if (texture == NULL)
            //SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

        return texture;
    }

struct GAME {
	SDL_Window *window;
    SDL_Renderer *renderer;
	void logErrorAndExit(const char* msg, const char* error)//ham thong bao loi
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
        SDL_Quit();
    }

	void init() { //ham khoi tao thu vien SDL,Window,renderer
         if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
            logErrorAndExit("SDL_Init", SDL_GetError());

        window = SDL_CreateWindow("angry_bird", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, scr_width, scr_height, SDL_WINDOW_SHOWN);
        //full screen
        //window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
        if (window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());

        if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
            logErrorAndExit( "SDL_image error:", IMG_GetError());

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
        //Khi chạy trong máy ảo (ví dụ phòng máy ở trường)
        //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

        if (renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(renderer, scr_width, scr_height);
    }
	void prepareScene(const char* filename) //ham load lai background;
    {
        SDL_RenderClear(renderer);
        SDL_Texture* texture_g;
        texture_g = loadTexture(renderer,filename);
        SDL_RenderCopy(renderer, texture_g, NULL, NULL);
    }

    void presentScene()// ham cap nhat man hinh
    {
        SDL_RenderPresent(renderer);
    }


    void renderTexture(SDL_Texture *texture, int x, int y)// ham ve toan bo texture len renderer tai 1 vi tri
    {
        SDL_Rect dest;
        dest.x = x;
        dest.y = y;
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

        SDL_RenderCopy(renderer, texture, NULL, &dest);
    }

    void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y) // ham ve 1 phan texture len man hinh
    {
        SDL_Rect dest;

        dest.x = x;
        dest.y = y;
        dest.w = src->w;
        dest.h = src->h;

        SDL_RenderCopy(renderer, texture, src, &dest);
    }

    void quit()// ham dong game
    {
        IMG_Quit();

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
};

class Blocks{
public:
    int type_b;
    SDL_Rect rect_b;
    SDL_Texture* texture_b;
    Blocks(int type = 0, int x = 0,int y=0) {
        type_b = type;
        rect_b.x = x;
        rect_b.y = y;
    }
    Blocks(int type, SDL_Rect& rect){
        type_b = type;
        rect_b = rect;
    }
    void render_b(SDL_Renderer* renderer){
        switch (type_b){
        case 1:
            texture_b = loadTexture(renderer,"wood.png");
            break;
        case 2:
            texture_b = loadTexture(renderer,"ice.png");
            break;
        case 3:
            texture_b = loadTexture(renderer,"rock.png");
            break;
        default:
            std::cout << "could not load blocks image"<< std::endl;
        }
    SDL_RenderCopy(renderer,texture_b,NULL,&rect_b);
    }
    void delete_blocks(){
        if(type_b == 0){
        SDL_DestroyTexture(texture_b);
        }
    }
};



class Map {
    int cols = 16;
    int rows = 14;
    vector<vector<int>> map_;
public:
    Map() : map_(cols,vector<int>(rows, 0)) {}
    void getmap(){
        int a[14][16]={{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,1,1,0,1,1,0,1,0,1,0,0,0,0,0}};
        for(int i = 0;i<rows;i++){
            for(int j = 0;j<cols;j++){
                map_[j][i] = a[i][j];
            }
        }
    }
    ~Map(){
        for (int i = 0; i < 16; ++i) {
            map_[i].clear();
            }
        map_.clear();
    }
    void render_map(SDL_Renderer* renderer)
    {
        for(int i = 0;i<rows;i++){
            for(int j = 0;j<cols;j++){
                if(map_[j][i]){
                    SDL_Rect dest;
                        dest.w = tile_size;
                        dest.h = tile_size;
                        dest.x = scr_width-scr_height+j*tile_size;
                        dest.y = i*tile_size;
                    Blocks block(map_[j][i],dest);
                    block.render_b(renderer);
                }
            }
        }
        SDL_RenderPresent(renderer);
        return;
    }

};
#endif // GAME-H
