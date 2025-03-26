#include"TextObject.h"

TextObject::TextObject()
{
    texture_=NULL;
}
TextObject::~TextObject()
{

}
bool TextObject::LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen)
{
    const char* string_val = str_val.c_str();
    SDL_Surface* text_surface = TTF_RenderText_Solid(font, string_val, text_color);
    if(text_surface){
        texture_ = SDL_CreateTextureFromSurface(screen,text_surface);
        width = text_surface->w;
        height = text_surface->h;
        SDL_FreeSurface(text_surface);
    }
    return texture_ != NULL;
}
void TextObject::Free()
{
    if(texture_!=NULL){
        SDL_DestroyTexture(texture_);
        texture_ = NULL;
    }
}
void TextObject::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
    text_color.r = red;
    text_color.g = green;
    text_color.b = blue;
}
void TextObject::RenderText(SDL_Renderer* screen, int x,int y, double angle/*=0.0*/, SDL_Point* center/* = NULL*/, SDL_RendererFlip flip /*= SDL_FLIP_NONE*/)
    {
        SDL_Rect renderQuad = {x,y,width,height};
        SDL_RenderCopyEx(screen, texture_,NULL, &renderQuad, angle,center,flip );
    }
