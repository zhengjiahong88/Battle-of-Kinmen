#include <SDL3_ttf/SDL_ttf.h>

#include "scene.h"
#include "state.h"

std::unique_ptr<Menu>  SceneBase::menu;
std::unique_ptr<Field> SceneBase::field;

Menu::Menu() : buttons( { { 640, 360 }, { 640, 90 } }, {0, 180}, 4, buttonsK) {
    TTF_Font* font = TTF_OpenFont("assets/standard.ttf", 120);
    title.init(font, "金門保衛戰", { 255, 255, 255, 255 });
    TTF_CloseFont(font);
    font = TTF_OpenFont("assets/standard.ttf", 120);
    hint.init(font, "", { 255, 255, 255, 255 });
    hut.init(font, "胡璉", { 255, 255, 255, 255 });
    lit.init(font, "李良榮", { 255, 255, 255, 255 });
    hu = createPicture("hu");
    li = createPicture("li");
}

Menu::~Menu() {
    SDL_DestroyTexture(hu);
    SDL_DestroyTexture(li);
}

void Menu::draw() const {
    title.draw({ { 0, 0 }, { 1920, 360 } });
    SDL_RenderTexture(Base::renderer, hu, nullptr, &HU_RECT);
    SDL_RenderTexture(Base::renderer, li, nullptr, &LI_RECT);
    // buttons.draw();
}

void Menu::handle() {
    if (Basemap::touched(HU_RECT)) {
        hut.draw({ { static_cast<Uint16>(Base::event.motion.x), static_cast<Uint16>(Base::event.motion.y) }, { 200, 40 } });
        if (Base::event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
            Base::id = 1;
            SceneBase::fieldStart();
        }
    }
    else if (Basemap::touched(LI_RECT)) {
        lit.draw({ { static_cast<Uint16>(Base::event.motion.x), static_cast<Uint16>(Base::event.motion.y) }, { 200, 40 } });
        if (Base::event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
            Base::id = 2;
            SceneBase::fieldStart();
        }
    }

    // buttons.handle();
}

Field::Field() : buttons( { { 1360, 920 }, { 40, 40 } }, {240, 0}, 2, buttonsK), toggle( { { 1360, 1000 }, { 280, 40 } }, k) {
    TTF_Font* font = TTF_OpenFont("assets/standard.ttf", 40);
    key.init(font, "難度：", { 255, 255, 255, 255 });
    value.init(font, "2", { 255, 255, 255, 255 });
    TTF_CloseFont(font);
    texture = createPicture("basemap");
}

void Field::handle() {
    if (Base::id == 1 && buttons.handle()) {
        TTF_Font* font = TTF_OpenFont("assets/standard.ttf", 40);
        char difficulty[4];
        itoa(State::difficulty, difficulty, 10);
        value.init(font, difficulty, { 255, 255, 255, 255 });
        TTF_CloseFont(font);
    }
    if (toggle.handle()) {
        if (Base::id == 1) State::serverReady = true;
        else if (Base::id == 2) State::clientReady = true;
    }
}

void Field::draw() const {
    constexpr SDL_FRect DST_RECT = { 0, 0, 1920, 1080 };
    SDL_RenderTexture(Base::renderer, texture, nullptr, &DST_RECT);
    key.draw({ { 1400, 840 }, { 200, 40 } });
    value.draw({ { 1400, 920 }, { 200, 40 } });
    if (Base::id == 1) buttons.draw();
    toggle.draw();
}

void SceneBase::init() {
    menu = std::make_unique<Menu>();
    field = std::make_unique<Field>();
    scene = menu.get();
}