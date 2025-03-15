#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include<vector>
#include<cmath>

const int screen_width = 640;
const int screen_height = 480;
const double g = 98;
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
class Bird{
private:
    // con tro tro den renderer
    SDL_Texture* m_texture;     // con tro tro den texture
    // hcn chua toa do va kich thuoc cua red
public:
    SDL_Renderer* m_renderer;
    SDL_Rect m_rect;
    Bird(SDL_Renderer* renderer, const char* imagePath, int x, int y);   // tao renderer va tai anh len toa do
    ~Bird(){
        SDL_DestroyTexture(m_texture);
    }         // ham xoa red
    void render()
    {
        SDL_RenderCopy(m_renderer, m_texture, NULL, &m_rect);
    }      //ham ve len man hinh
    void setPosition(int x, int y)
    {
        m_rect.x = x;
        m_rect.y = y;
    } // ham dat toa do
};
Bird :: Bird(SDL_Renderer* renderer, const char* imagePath, int x, int y)
    : m_renderer(renderer) {// tro den con tro renderer
    m_texture = createxture(m_renderer, imagePath);
    // Khởi tạo tọa độ
    m_rect.x = x;
    m_rect.y = y;
    SDL_QueryTexture(m_texture, NULL, NULL, &m_rect.w, &m_rect.h);
}

void banChim(Bird& chim, double gocBan, double lucBan) {
    // Chuyển đổi góc bắn từ độ sang radian

double gocRadian = gocBan * M_PI / 180.0;

    // Tính toán vận tốc ban đầu theo trục x và y
    double vanTocX = lucBan * cos(gocRadian);
    double vanTocY = -lucBan * sin(gocRadian); // Dấu âm vì trục y hướng xuống

    // Đặt vị trí ban đầu của chim
    int x = chim.m_rect.x;
    int y = chim.m_rect.y;
    chim.setPosition( x, y);
    // Thời gian mô phỏng (có thể điều chỉnh)
    double thoiGian = 0.0;
    double buocThoiGian = 0.01; // Bước thời gian nhỏ để mô phỏng mượt mà

    // Gia tốc trọng trường (có thể điều chỉnh)
    double giaTocTrongTruong = g;

    // Vòng lặp mô phỏng quỹ đạo bay
    while (chim.m_rect.y < 480) { // Giả sử chiều cao màn hình là 480
        // Tính toán vị trí mới
        double viTriX = x + vanTocX * thoiGian;
        double viTriY = y + vanTocY * thoiGian + 0.5 * giaTocTrongTruong * thoiGian * thoiGian;
        if(viTriX > screen_width|| viTriY > screen_height){break; return;}

        // Cập nhật vị trí của chim
        chim.setPosition(static_cast<int>(viTriX), static_cast<int>(viTriY));

        // Vẽ chim
        chim.render();
        SDL_RenderPresent(chim.m_renderer);
        SDL_RenderClear(chim.m_renderer);
        SDL_Delay(5);

        // Cập nhật thời gian
        thoiGian += buocThoiGian;
    }
}
void handleEvents(Bird& chim, double& gocBan, double& lucBan, double tocDoTangLuc, SDL_Event e) {
    bool dangGiuSpace = false;
    if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_UP:
                    chim.m_rect.y += 1.0;
                    break;
                case SDLK_DOWN:
                    chim.m_rect.y -= 1.0;
                    break;
                case SDLK_LEFT:
                    gocBan -= 5.0;
                    break;
                case SDLK_RIGHT:
                    gocBan += 5.0;
                    break;
                case SDLK_SPACE:
                    dangGiuSpace = true;
                    lucBan += tocDoTangLuc;
                    break;
                default:
                    break;
            }
            std::cout << "do cao " << chim.m_rect.y << ", goc ban " << gocBan << ", luc ban " << lucBan << std::endl;
        } else if (e.type == SDL_KEYUP) {
                if(e.key.keysym.sym == SDLK_SPACE) {
            dangGiuSpace = false;
            banChim(chim, gocBan, lucBan);

            lucBan = 250.0;
            tocDoTangLuc = 3;
            return;
            // Reset lực bắn sau khi bắn
        }
    }
}
int main(int argc, char* argv[]) {
    // Khởi tạo SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL không thể khởi tạo! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    // Tạo cửa sổ
    SDL_Window* window = SDL_CreateWindow("Chim", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width,screen_height, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Cửa sổ không thể được tạo! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Tạo renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer không thể được tạo! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Khởi tạo SDL_image
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        std::cerr << "SDL_image không thể khởi tạo! IMG_Error: " << IMG_GetError() << std::endl;
        return 1;
    }

    double gocBan = 45.0;
    double lucBan = 250.0;
    double tocDoTangLuc = 25.0;

    SDL_Event e;
    int i = 0 ;
    bool quit = false;
    while (!quit) {
            i = i%3;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if(i==0){
                            Bird red(renderer, "red.png", 20, 250);
                            red.render();
                            handleEvents(red, gocBan, lucBan, tocDoTangLuc,e);
                            SDL_RenderClear(red.m_renderer);
                        }
            else if(i==1){
                            Bird blue(renderer, "blue.png", 20, 250);
                            blue.render();
                            handleEvents(blue, gocBan, lucBan, tocDoTangLuc,e);
                            SDL_RenderClear(blue.m_renderer);
                }
            else if(i==2){
                            Bird black(renderer, "black.png", 20, 250);
                            black.render();
                            handleEvents(black, gocBan, lucBan, tocDoTangLuc,e);
                            SDL_RenderClear(black.m_renderer);
                }

            }
            i++;
        }

    SDL_RenderPresent(renderer);

    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
