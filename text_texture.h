#ifndef UNTITLED_TEXT_TEXTURE_H
#define UNTITLED_TEXT_TEXTURE_H

#include <SDL3_ttf/SDL_ttf.h>

#include "data.h"

struct TextTexture {
    SDL_Texture* texture{};
    FSize size{};

    ~TextTexture() {SDL_DestroyTexture(texture);}

    void init(TTF_Font *font, const char *text, SDL_Color color);

    void draw(Rect rect) const;
};

#endif //UNTITLED_TEXT_TEXTURE_H