#include <SDL3_ttf/SDL_ttf.h>

#include "scene.h"
#include "state.h"

std::unique_ptr<Menu>  SceneBase::menu;
std::unique_ptr<Field> SceneBase::field;

Menu::Menu() : buttons( { { 640, 360 }, { 640, 90 } }, 180, 4, buttonsK) {
    TTF_Font* font = TTF_OpenFont("assets/standard.ttf", 120);
    if (!font) { SDL_Log("TTF_OpenFont failed: %s", SDL_GetError()); }
    texture.init(font, "金門保衛戰", { 255, 255, 255, 255 });
    TTF_CloseFont(font);
}

void Menu::draw() const {
    texture.draw({ { 0, 0 }, { 1920, 360 } });
    buttons.draw();
}

void Field::handle() {
    if (toggle.handle()) {
        if (Base::id == 1) State::serverReady = true;
        else if (Base::id == 2) State::clientReady = true;
    }
}

void Field::draw() const {
    constexpr SDL_FRect DST_RECT = { 0, 0, 1920, 1080 };
    SDL_RenderTexture(Base::renderer, texture, nullptr, &DST_RECT);
    toggle.draw();
}

void SceneBase::init() {
    menu = std::make_unique<Menu>();
    field = std::make_unique<Field>();
    scene = menu.get();
}