#ifndef UNTITLED_BUTTONS_H
#define UNTITLED_BUTTONS_H

#include <SDL3_ttf/SDL_ttf.h>

#include "data.h"
#include "text_texture.h"

struct Buttons
{
    Rect rect;
    Uint16 gap;
    Uint8 num;
    const char** strings;
    SDL_Renderer* renderer;

    SDL_Texture** textures;
    Uint8 level = 255;
    FSize* sizes = new FSize[num];

    Buttons(const Rect rect, const Uint16 gap, const Uint8 num, const char** strings, SDL_Renderer* renderer) : rect(rect), gap(gap), num(num), strings(strings), renderer(renderer)
    {
        textures = createTextTextures(sizes, renderer, { 0, 0, 0, 255 }, strings, rect.size.h, num);
    }

    ~Buttons()
    {
        for (int i = 0; i < num; i++) SDL_DestroyTexture(textures[i]);
        delete[] textures;
        delete[] sizes;
    }

    Uint8 handle(const SDL_Event& e)
    {
        Rect r = rect;
        level = 255;
        for (int i = 0; i < num; i++)
        {
            if (r.inRange(e.motion))
            {
                level = i;
                if (e.type == SDL_EVENT_MOUSE_BUTTON_UP) return level;
                if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) level += num;
                return 255;
            }
            r.pos.y += gap;
        }
        return 255;
    }

    void draw() const
    {
        Uint8 c = 255;
        Rect r = rect;
        for (int i = 0; i < num; i++)
        {
            if (level != 255 && i == level % num) c -= (level / num + 1) * 85;
            else c = 255;
            SDL_SetRenderDrawColor(renderer, c, c, c, 255);
            SDL_FRect button = r.toFRect();
            SDL_RenderFillRect(renderer, &button);
            drawTextTexture(renderer, textures[i], sizes[i], r);
            r.pos.y += gap;
        }
    }
};
#endif //UNTITLED_BUTTONS_H