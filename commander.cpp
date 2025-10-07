#include "commander.h"
#include "state.h"

Commander::Commander(const std::string& file, const std::string& name, const SDL_FRect rect, const int num)
    : rect(rect), num(num) {
    headshot.init(name, rect, 40, 255);
    headshot.initImage("headshot/" + file);
    start.init("開始", {1360, 1000, 280, 40}, 40, 0);
}

void Commander::handle() {
    for (int i = 0; i < num; i++) if (armyButtons[i].icon.handle()) choice = i;
    start.handle();
    if (Base::event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
        float x, y;
        SDL_GetMouseState(&x, &y);
        if (const MapPos pos = toMap({x, y}); inRange(pos) && basemap[pos] != 'S') armyButtons[choice].target = toF(pos);
    }
}

void Commander::draw() {
    for (int i = 0; i < num; i++) {
        armyButtons[i].move();
        armyButtons[i].icon.draw();
    }
    start.draw();
}

Hu::Hu() : Commander("hu", "胡璉", {1248.f, 376.f, 168.f, 224.f}, 12) {
    for (int i = 0; i < 12; i++) {
        const float x = i % 3;
        const float y = i / 3;
        armyButtons[i].init("步兵團", "army/roc", {240 * x + 1200, 160 * y + 240});
    }
    key.init("難度", 40, 255);
    value.init("2", 40, 255);
    add.init("+", {1360, 920, 40, 40}, 40, 0);
    sub.init("-", {1600, 920, 40, 40}, 40, 0);
}

void Hu::handle() {
    Commander::handle();
    if (add.handle()) {
        difficulty++;
        value.init(std::to_string(difficulty), 40, 255);
    }
    if (sub.handle()) {
        difficulty--;
        value.init(std::to_string(difficulty), 40, 255);
    }
}

void Hu::draw() {
    Commander::draw();
    value.draw({1360, 920, 280, 40});
    key.draw({1360, 840, 280, 40});
    add.draw();
    sub.draw();
}

Li::Li() : Commander("li", "李良榮", {1584, 376, 168, 224}, 12) {
    for (int i = 0; i < 12; i++) {
        const float x = i % 3;
        const float y = i / 3;
        const FPos rect = {240 * x + 1200, 160 * y + 240};
        if (i < 8) armyButtons[i].init("步兵團", "army/roc", rect);
        else if (i == 8) armyButtons[i].init("戰車營", "army/tank", rect);
        else if (i == 11) armyButtons[i].init("工兵營", "army/engineer", rect);
        else armyButtons[i].init("砲兵連", "army/artillery", rect);
    }
}