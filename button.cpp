#include "button.h"
#include "basemap.h"

void Button::init(const std::string& name, const SDL_FRect r, const Uint16 size, const Uint8 color) {
    rect = r;
    text.init(name, size, color);
}

bool Button::handle() {
    touch = touched(rect);
    if (touch) {
        down = Base::event.type == SDL_EVENT_MOUSE_BUTTON_DOWN;
        if (Base::event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
            return true;
        }
    }
    return false;
}

void TextButton::draw() const {
    const Uint8 c = touch ? (2 - down) * 85 : 255;
    SDL_SetRenderDrawColor(Base::renderer, c, c, c, 255);
    SDL_RenderFillRect(Base::renderer, &rect);
    text.draw(rect);
}

void ImageButton::draw() const {
    image.draw(rect);
    if (touch) {
        float x, y;
        SDL_GetMouseState(&x, &y);
        const SDL_FRect tip{ x, y, text.size.w, text.size.h };
        text.draw(tip);
    }
}
