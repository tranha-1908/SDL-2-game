
#include"BASE_OBJECT.h"

BaseObject::BaseObject()
{
    p_object_=NULL;
    rect_.x=0;
    rect_.y=0;
    rect_.h=0;
    rect_.w=0;
}
BaseObject::~BaseObject()
{
    free();
}
bool BaseObject::LoadImg(const char* filename, SDL_Renderer* screen)
{
        SDL_Texture* new_texture = NULL;
        SDL_Surface* load_surface = IMG_Load(filename);
        if(load_surface!=NULL)
        {
            new_texture=SDL_CreateTextureFromSurface(screen,load_surface);
            if(new_texture!=NULL)
            {
                rect_.w = load_surface->w;
                rect_.h = load_surface->h;
            }
            SDL_FreeSurface(load_surface);
        }
        p_object_= new_texture;
        return p_object_ != NULL;
}
void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip)
{
    SDL_Rect render_q = {rect_.x, rect_.y,rect_.w,rect_.h};
    SDL_RenderCopy(des, p_object_,clip,&render_q);
}
void BaseObject::free()
{
    if(p_object_=NULL)
    {
        SDL_DestroyTexture(p_object_);
        p_object_=NULL;
        rect_.h=0;
        rect_.w = 0;
    }
}
void BaseObject:: waitUntilKeyPress()
{
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
void BaseObject::waitMouseButton()
{
    SDL_Event event;
    bool mouseButton = false;

    while (!mouseButton) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                mouseButton = true;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    if(event.motion.x>458 && event.motion.x <680 && event.motion.y >246 && event.motion.y <394)
                    mouseButton = true;
                }
            }
        }
        SDL_Delay(10); // Tránh chiếm dụng quá nhiều CPU
    }
}
