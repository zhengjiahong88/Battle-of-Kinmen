#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <string>

#include "texture.h"

void TextTexture::init(TTF_Font* font, const char* text, const SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Blended(font, text, 0, color);
    if (texture) SDL_DestroyTexture(texture);
    texture = SDL_CreateTextureFromSurface(Base::renderer, surface);
    SDL_DestroySurface(surface);
    float w = 0, h = 0;
    SDL_GetTextureSize(texture, &w, &h);
    size = {w, h};
}

void TextTexture::draw(const Rect rect) const {
    const SDL_FRect string = toFRect(rect.pos + (rect.size - size) / 2, size);
    SDL_RenderTexture(Base::renderer, texture, nullptr, &string);
}

SDL_Texture *createPicture(const char *name) {
    SDL_Surface* surface = IMG_Load(("assets/picture/" + std::string(name) + ".png").c_str());
    SDL_Texture *texture = SDL_CreateTextureFromSurface(Base::renderer, surface);
    SDL_DestroySurface(surface);
    return texture;
}