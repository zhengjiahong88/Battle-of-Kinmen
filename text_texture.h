#ifndef UNTITLED_TEXT_TEXTURE_H
#define UNTITLED_TEXT_TEXTURE_H

#include "base.h"
#include "data.h"

struct TextTexture {
    SDL_Texture* texture;
    FSize size{};

    TextTexture(TTF_Font *font, const char *text, SDL_Color color);

    ~TextTexture() {SDL_DestroyTexture(texture);}

    void draw(Rect rect) const;
};

#endif //UNTITLED_TEXT_TEXTURE_H