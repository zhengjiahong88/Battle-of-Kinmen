#ifndef UNTITLED_BUTTONS_H
#define UNTITLED_BUTTONS_H

#include "base.h"
#include "data.h"
#include "button.h"
#include "texture.h"

struct Buttons
{
    Rect rect;
    Size gap;
    Uint8 num;
    Button** buttons;
    bool down = false;
    TextTexture* textures{};
    Uint8 level = 255;

    Buttons(Rect rect, Size gap, Uint8 num, Button* buttons[]);

    ~Buttons() { delete[] textures; }

    bool handle();

    void draw() const;
};
#endif //UNTITLED_BUTTONS_H