#ifndef _BIRD__H
#define _BIRD__H
#include<cmath>
    double gocBan = 45.0;
    double lucBan = 250.0;
    double tocDoTangLuc = 25.0;
    double giaTocTrongTruong = 98   ;
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

class Bird{
public:
    int type_bird;
    SDL_Texture* texture_bird;
    SDL_Rect rect_bird;

    Bird(int type =0, int x = 40,int y = 250){
        type_bird = type;
        rect_bird.x = x;
        rect_bird.y = y;
    }
    Bird(int type, SDL_Rect& rect){
        type_bird = type;
        rect_bird = rect;
    }
    void die(){

    }         // ham xoa red
    void render_bird(SDL_Renderer* renderer)
    {
        switch (type_bird){
        case 1:
            texture_bird = loadTexture(renderer,"red.png");
            break;
        case 2:
            texture_bird = loadTexture(renderer,"blue.png");
            break;
        case 3:
            texture_bird = loadTexture(renderer,"black.png");
            break;
        default:
            std::cout << "could not load bird image"<< std::endl;
        }

    SDL_RenderCopy(renderer,texture_bird,NULL,&rect_bird);
    }      //ham ve len man hinh
    SDL_Rect getrect(){
        return rect_bird;
    }
    void setPosition(int x, int y)
    {
        rect_bird.x = x;
        rect_bird.y = y;
    }
};

bool impact_bird_block(const Bird& chim, const Map& map_) {
        //SDL_Rect chimRect = chim.getrect();
        //int x = (chimRect.x - scr_width + scr_height)/tile_size;
       // int y = chimRect.y/tile_size;

    return false;
}
void banChim(Bird& chim, GAME& game,Map& map_1, double gocBan, double lucBan) {
    // Chuyển đổi góc bắn từ độ sang radian
    double gocRadian = gocBan * M_PI / 180.0;

    // Tính toán vận tốc ban đầu theo trục x và y
    double vanTocX = lucBan * cos(gocRadian);
    double vanTocY = -lucBan * sin(gocRadian); // Dấu âm vì trục y hướng xuống

    // Đặt vị trí ban đầu của chim
    int x = chim.rect_bird.x;
    int y = chim.rect_bird.y;
    chim.setPosition(x, y);

    // Thời gian mô phỏng
    double thoiGian = 0.0;
    bool is_move = true;

    while (is_move) {
        // Tính toán thời gian trôi qua

        // Tính toán vị trí mới dựa trên thời gian delta
        double viTriX = x + vanTocX * thoiGian;
        double viTriY = y + vanTocY * thoiGian + 0.5 * giaTocTrongTruong * thoiGian * thoiGian;

        if (viTriX > scr_width || viTriY > scr_height-40) {
            is_move = false;
            chim.delete_bird();
            game.presentScene();
            return;
        }

        // Cập nhật vị trí của chim
        chim.setPosition(static_cast<int>(viTriX), static_cast<int>(viTriY));

        if(impact_bird_block(chim,map_1)){
                is_move = false;


        }
        // Vẽ chim
        chim.render_bird(game.renderer);

        // Vẽ tất cả các đối tượng và cập nhật màn hình
        //SDL_RenderClear(game.renderer);
        game.prepareScene("background.jpg");
        if(is_move){
            map_1.render_map(game.renderer);
        }
        // vẽ lại background nếu cần
        chim.render_bird(game.renderer);
        SDL_RenderPresent(game.renderer);
        thoiGian += 0.08        ;
        // Điều chỉnh tốc độ mô phỏng (nếu cần)
    }
}

void handleEvents(Bird& chim, GAME& game,Map& map_1, double& gocBan, double& lucBan, double tocDoTangLuc, SDL_Event e) {
    bool dangGiuSpace = false;
    if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_UP:
                    chim.rect_bird.y += 1.0;
                    break;
                case SDLK_DOWN:
                    chim.rect_bird.y -= 1.0;
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
            std::cout << "do cao " << chim.rect_bird.y << ", goc ban " << gocBan << ", luc ban " << lucBan << std::endl;
        } else if (e.type == SDL_KEYUP) {
                if(e.key.keysym.sym == SDLK_SPACE) {
            dangGiuSpace = false;
            banChim(chim, game, map_1, gocBan, lucBan);

            lucBan = 250.0;
            tocDoTangLuc = 3;
            return;
            // Reset lực bắn sau khi bắn
        }
    }
}
#endif
