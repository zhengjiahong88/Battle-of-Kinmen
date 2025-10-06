#include "commander.h"
#include "state.h"

Commander::Commander(const std::string& file, const std::string& name, const SDL_FRect rect, const int num)
    : rect(rect), num(num) {
    headshot.init(name, rect, 40, 255);
    headshot.initImage("headshot/" + file);
    armyButtons = new Army[num];
}

Hu::Hu() : Commander("hu", "胡璉", {1248.f, 376.f, 168.f, 224.f}, 12) {
    for (int i = 0; i < 12; i++) {
        const float x = i % 3;
        const float y = i / 3;
        armyButtons[i].init("步兵團", "army/roc", {240 * x + 1200, 160 * y + 240});
    }
}

void Commander::handle() {
    for (int i = 0; i < num; i++) {
        armyButtons[i].move();
        if (armyButtons[i].icon.handle()) choice = i;
    }
    if (Base::event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
        float x, y;
        SDL_GetMouseState(&x, &y);
        if (const MapPos pos = toMap({x, y}); inRange(pos)) armyButtons[choice].target = toF(pos);
    }
}

void Commander::draw() {
    for (int i = 0; i < num; i++) armyButtons[i].icon.draw();
}