#ifndef UNTITLED_BUTTONS_H
#define UNTITLED_BUTTONS_H

#include <string>

#include "data.h"
#include "texture.h"

struct Button {
    virtual ~Button() = default;

    SDL_FRect rect;
    TextTexture text;
    bool touch = false;
    bool down = false;

    virtual void init(const std::string& name, SDL_FRect r, Uint16 size, Uint8 color);

    virtual bool handle();

    virtual void draw() const {}
};

struct TextButton final : Button {
    void draw() const override;
};

struct ImageButton final : Button {
    ImageTexture image;
    void initImage(const std::string& path) {image.init(path);}
    void draw() const override;
};

#endif //UNTITLED_BUTTONS_H