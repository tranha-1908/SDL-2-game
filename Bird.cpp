#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include<cmath>
const int screen_width = 640;
const int screen_height = 480;
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
class Red{
private:
    // con tro tro den renderer
    SDL_Texture* m_texture;     // con tro tro den texture
    SDL_Rect m_rect;    // hcn chua toa do va kich thuoc cua red
public:
    SDL_Renderer* m_renderer;
    Red(SDL_Renderer* renderer, const char* imagePath, int x, int y);   // tao renderer va tai anh len toa do
    ~Red(){
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
    SDL_Rect getRect(){
        return m_rect;
    }     // tra ve hcn chua toa do


};

Red::Red(SDL_Renderer* renderer, const char* imagePath, int x, int y)
    : m_renderer(renderer) {// tro den con tro renderer
    m_texture = createxture(m_renderer, imagePath);
    // Khởi tạo tọa độ
    m_rect.x = x;
    m_rect.y = y;
    SDL_QueryTexture(m_texture, NULL, NULL, &m_rect.w, &m_rect.h);
}



class Blue{
private:

    SDL_Texture *m_texture;
    SDL_Rect m_rect;
public:
    SDL_Renderer *m_renderer;
    Blue(SDL_Renderer *renderer, const char* imagePath,int x,int y);
    ~Blue(){
        SDL_DestroyTexture(m_texture);
    }

    void render()
    {
        SDL_RenderCopy(m_renderer, m_texture, NULL, &m_rect);
    }
    void setPosition(int x, int y)
    {
        m_rect.x = x;
        m_rect.y = y;
    }
    SDL_Rect getRect()
    {
        return m_rect;
    }


};
Blue::Blue(SDL_Renderer *renderer,const char*imagePath,int x,int y)
     :m_renderer(renderer)
     {
            m_texture = createxture(m_renderer,imagePath);
            m_rect.x = x;
            m_rect.y = y;
            SDL_QueryTexture(m_texture, NULL, NULL , &m_rect.w,&m_rect.h);
     }

class Black{
private:

    SDL_Texture* m_texture;
    SDL_Rect m_rect;
public:
     SDL_Renderer* m_renderer;
    Black(SDL_Renderer* renderer, const char* imagePath, int x, int y);
    ~Black()
    {
        SDL_DestroyTexture(m_texture);
    }
    void render(){
        SDL_RenderCopy(m_renderer, m_texture, NULL, &m_rect);
    }
    void setPosition(int x,int y)
    {
        m_rect.x = x;
        m_rect.y = y;
    }
    SDL_Rect getRect(){
        return m_rect;
    }
};
Black::Black(SDL_Renderer* renderer, const char* imagePath, int x, int y)
    :m_renderer(renderer){
        m_texture = createxture(renderer,imagePath);
        m_rect.x = x;
        m_rect.y = y;
        SDL_QueryTexture(m_texture,NULL,NULL, &m_rect.w,&m_rect.h);
    }
template <typename T>
void banChim(T& chim, int x, int y, double doCao, double gocBan, double lucBan) {
    // Chuyển đổi góc bắn từ độ sang radian
    double gocRadian = gocBan * M_PI / 180.0;

    // Tính toán vận tốc ban đầu theo trục x và y
    double vanTocX = lucBan * cos(gocRadian);
    double vanTocY = -lucBan * sin(gocRadian); // Dấu âm vì trục y hướng xuống

    // Đặt vị trí ban đầu của chim
    chim.setPosition(x, y);

    // Thời gian mô phỏng (có thể điều chỉnh)
    double thoiGian = 0.0;
    double buocThoiGian = 0.01; // Bước thời gian nhỏ để mô phỏng mượt mà

    // Gia tốc trọng trường (có thể điều chỉnh)
    double giaTocTrongTruong = doCao;

    // Vòng lặp mô phỏng quỹ đạo bay
    while (chim.getRect().y < 480) { // Giả sử chiều cao màn hình là 480
        // Tính toán vị trí mới
        double viTriX = x + vanTocX * thoiGian;
        double viTriY = y + vanTocY * thoiGian + 0.5 * giaTocTrongTruong * thoiGian * thoiGian;
        if(viTriX > screen_width|| viTriY > screen_height){return;}

        // Cập nhật vị trí của chim
        chim.setPosition(static_cast<int>(viTriX), static_cast<int>(viTriY));

        // Vẽ chim
        chim.render();
        SDL_RenderPresent(chim.m_renderer);
        SDL_RenderClear(chim.m_renderer);
        SDL_Delay(10);

        // Cập nhật thời gian
        thoiGian += buocThoiGian;
    }
}
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

    // Tạo đối tượng chim Red
    Red red(renderer, "red.png", 10, 45);
    Blue blue(renderer, "blue.png", 150,50);
    Black black(renderer, "black.png", 200,50);
    // Vòng lặp chính
    SDL_Event e;
    bool quit = false;
    while (!quit) {
        waitUntilKeyPress();


        // Xóa màn hình
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Vẽ chim Red
        red.render();
        banChim(red, 10, 300, 100.0, 30.0, 300);


        // Cập nhật màn hình
        blue.render();
        banChim(blue, 10, 300, 100.0, 30.0, 200);
        black.render();
        banChim(black, 10, 300, 100.0, 30.0, 300);
        SDL_RenderPresent(renderer);
    }

    // Giải phóng bộ nhớ
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
