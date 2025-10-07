#ifndef BATTLE_OF_KINMEN_HU_H
#define BATTLE_OF_KINMEN_HU_H

#include "button.h"
#include "army.h"

struct Commander {
    ImageButton headshot;
    TextButton start;
    SDL_FRect rect;
    Army armyButtons[12];
    int num, choice = 0;
    Commander(const std::string& file, const std::string& name, SDL_FRect rect, int num);

    virtual ~Commander() = default;
    virtual void handle();
    virtual void draw();
};

struct Hu final : Commander {
    TextTexture key, value;
    TextButton add, sub;
    Hu();
    void handle() override;
    void draw() override;
};

struct Li final : Commander {
    Li();
};

#endif //BATTLE_OF_KINMEN_HU_H