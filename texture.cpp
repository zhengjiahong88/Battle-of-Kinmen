#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <string>

#include "texture.h"

void TextTexture::init(const std::string& text, Uint16 s, const Uint8 color) {
    TTF_Font* font = TTF_OpenFont("assets/standard.ttf", s);
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), 0, {color, color, color, 255});
    if (texture) SDL_DestroyTexture(texture);
    texture = SDL_CreateTextureFromSurface(Base::renderer, surface);
    SDL_DestroySurface(surface);
    float w = 0, h = 0;
    SDL_GetTextureSize(texture, &w, &h);
    size = {w, h};
    TTF_CloseFont(font);
}

void TextTexture::draw(const SDL_FRect rect) const {
    const SDL_FRect string = together((toSize(rect) - size) / 2 + toPos(rect), size);
    SDL_RenderTexture(Base::renderer, texture, nullptr, &string);
}

void ImageTexture::init(const std::string& path) {
    SDL_Surface* surface = IMG_Load(("assets/picture/" + path + ".png").c_str());
    texture = SDL_CreateTextureFromSurface(Base::renderer, surface);
    SDL_DestroySurface(surface);
}

void ImageTexture::draw(const SDL_FRect rect) const {
    SDL_RenderTexture(Base::renderer, texture, nullptr, &rect);
}