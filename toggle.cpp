#include <SDL3_ttf/SDL_ttf.h>

#include "toggle.h"

Toggle::Toggle(const Rect rect, const char *texts[2]) : rect(rect), texts(texts) {
    TTF_Font *font = TTF_OpenFont("assets/standard.ttf", rect.size.h);
    for (int i = 0; i < 2; i++) textures[i].init(font, texts[i], {0, 0, 0, 255});
    TTF_CloseFont(font);
}

bool Toggle::handle() {
    touch = rect.inRange();
    down = Base::event.type == SDL_EVENT_MOUSE_BUTTON_DOWN;
    if (Base::event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
        index = !index;
        return true;
    }
    return false;
}

void Toggle::draw() const {
    const Uint8 c = touch ? (2 - down) * 85 : 255;
    SDL_SetRenderDrawColor(Base::renderer, c, c, c, 255);
    const SDL_FRect fRect = rect.toFRect();
    SDL_RenderFillRect(Base::renderer, &fRect);
    textures[index].draw(rect);
}