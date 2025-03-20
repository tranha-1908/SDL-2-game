#ifndef BASE_OBJECT__
#define BASE_OBJECT__

#include"COMMON_FUNC.h"

class BaseObject
{
public:
    BaseObject();
    ~BaseObject();
    void SetRect(const int&x, const int& y){ rect_.x = x; rect_.y = y;}
    SDL_Rect GetRect() const {return rect_;}
    SDL_Texture* GetObject() const{return p_object_;}

    bool LoadImg(const char* filename, SDL_Renderer* screen);
    void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
    void free();
protected:
    SDL_Texture* p_object_;
    SDL_Rect rect_;

};

#endif // BASE_OBJECT__
