#ifndef BATTLE_OF_KINMEN_HU_H
#define BATTLE_OF_KINMEN_HU_H

#include "button.h"
#include "army.h"

struct Commander {
    ImageButton headshot;
    SDL_FRect rect;
    Army *armyButtons;
    int choice = 0;
    int num;
    Commander(const std::string& file, const std::string& name, SDL_FRect rect, int num);

    virtual ~Commander() {delete[] armyButtons;}
    virtual void handle();
    virtual void draw();
};

struct Hu final : Commander {
    Hu();
};

struct Li final : Commander {
    Li() : Commander("li", "李良榮", {1584, 376, 168, 224}, 12) {}
};

#endif //BATTLE_OF_KINMEN_HU_H