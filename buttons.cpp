#include <SDL3_ttf/SDL_ttf.h>

#include "buttons.h"
#include "texture.h"
#include "basemap.h"

Buttons::Buttons(const Rect rect, const Size gap, const Uint8 num, Button* buttons[]) : rect(rect), gap(gap), num(num), buttons(buttons) {
    textures = new TextTexture[num];
    TTF_Font* font = TTF_OpenFont("assets/standard.ttf", rect.size.h);
    for (int i = 0; i < num; i++) textures[i].init(font, buttons[i]->name, {0, 0, 0, 255});
    TTF_CloseFont(font);
}

bool Buttons::handle() {
    Rect r = rect;
    level = 255;
    for (int i = 0; i < num; i++) {
        if (Basemap::touched(r.toFRect())) {
            level = i;
            down = Base::event.type == SDL_EVENT_MOUSE_BUTTON_DOWN;
            if (Base::event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
                buttons[i]->handle();
                return true;
            }
        }
        r.pos += gap;
    }
    return false;
}

void Buttons::draw() const {
    Rect r = rect;
    for (int i = 0; i < num; i++) {
        const Uint8 c = i == level ? (2 - down) * 85 : 255;
        SDL_SetRenderDrawColor(Base::renderer, c, c, c, 255);
        SDL_FRect button = r.toFRect();
        SDL_RenderFillRect(Base::renderer, &button);
        textures[i].draw(r);
        r.pos += gap;
    }
}