/*#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
using namespace std;
const int screen_width = 1200;
const int screen_height = 640;
const int tile_size = 40;
void waitUntilKeyPress() {
    SDL_Event event;
    bool keyPressed = false;

    while (!keyPressed) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                // Người dùng đóng cửa sổ
                exit(0);
            } else if (event.type == SDL_KEYDOWN) {
                // Người dùng nhấn một phím
                keyPressed = true;
            }
        }
        SDL_Delay(10); // Tránh chiếm dụng quá nhiều CPU
    }
}
SDL_Texture* createxture(SDL_Renderer* renderer, const char* imagePath){
    SDL_Surface* surface = IMG_Load(imagePath);
    if (!surface) {
        std::cerr << "Không thể tải ảnh: " << IMG_GetError() << std::endl;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface); // tao texture tu anh
    SDL_FreeSurface(surface);
    if (!texture) {
        std::cerr << "Không thể tạo texture: " << SDL_GetError() << std::endl;
    }
    return texture;

}
class Game{
public:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;

    Game();
    void render();
    void run();
    ~Game();

};
Game::Game(){
    bool running = true;
    if(SDL_Init(SDL_INIT_VIDEO<0)){
        cerr<< "SDL could not intialize " << SDL_GetError() << endl;
        running = false;
    }

    window = SDL_CreateWindow("Angry_bird", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width,screen_height, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Cửa sổ không thể được tạo! SDL_Error: " << SDL_GetError() << std::endl;
        running = false;
    }

    // Tạo renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer không thể được tạo! SDL_Error: " << SDL_GetError() << std::endl;
        running = false;
    }

    // Khởi tạo SDL_image
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        std::cerr << "SDL_image không thể khởi tạo! IMG_Error: " << IMG_GetError() << std::endl;
        running = false;
    }
    SDL_Texture* texture = createxture(renderer,"background.jpg");
    SDL_RenderCopy(renderer,texture,NULL,NULL);
    SDL_RenderPresent(renderer);
}
Game::~Game(){
    SDL_DestroyRenderer(renderer);
}
void Game::render(){
    SDL_SetRenderDrawColor(renderer,128,128,128,255);
    int x = screen_height/tile_size;
    int Map[x][x] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},};
    for(int i = 0;i<x;i++){
        for(int j = 0;j<x;j++){
            if(Map[i][j]==1){
                SDL_Rect tile ;
                tile.w = tile_size;
                tile.h = tile_size;
                tile.x = screen_width-screen_height+j*tile_size;
                tile.y =  i*tile_size;
                SDL_Texture* m_texture = createxture(renderer,"wood.png");
                SDL_QueryTexture(m_texture, NULL, NULL,&tile.w,&tile.h );
                SDL_RenderCopy(renderer,m_texture,NULL,&tile);
            }
        }
    }
    SDL_RenderPresent(renderer);
}
*/
