#ifndef UNTITLED_TEXT_TEXTURE_H
#define UNTITLED_TEXT_TEXTURE_H

#include <string>

#include "data.h"

struct TextTexture {
    SDL_Texture* texture = nullptr;
    FSize size{};

    ~TextTexture() {SDL_DestroyTexture(texture);}

    void init(const std::string& text, Uint16 s, Uint8 color);

    void draw(SDL_FRect rect) const;
};

struct ImageTexture {
    SDL_Texture* texture = nullptr;

    ~ImageTexture() {SDL_DestroyTexture(texture);}

    void init(const std::string& path);

    void draw(SDL_FRect rect) const;
};

#endif //UNTITLED_TEXT_TEXTURE_H