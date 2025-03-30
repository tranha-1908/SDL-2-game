#ifndef TEXT_OBJECT_H
#define TEXT_OBJECT_H

#include "COMMON_FUNC.h"

class TextObject
{
public:
    TextObject();
    ~TextObject();


    bool LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen);
    void Free();
    void SetColor(Uint8 alpha, Uint8 red, Uint8 green, Uint8 blue);

    void RenderText(SDL_Renderer* screen, int x,int y, double angle=0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    int GetWidth() const {return width;}
    int GetHeight() const {return height;}
    void SetText(std::string text){str_val = text;}
    std::string GetText() const {return str_val;}
private:
    std::string str_val;
    SDL_Texture* texture_;
    SDL_Color text_color;
    int width;
    int height;
};
#endif // TEXT_OBJECT_H
