#ifndef BATTLE_OF_KINMEN_HU_H
#define BATTLE_OF_KINMEN_HU_H

#include <vector>

#include "button.h"
#include "army.h"
#include "basemap.h"

struct Commander {
    ImageButton headshot;
    TextButton start;
    SDL_FRect rect;
    Basemap basemap;
    Army self[12]{}, friendly[12]{};
    std::vector<Army> enemy;
    int difficulty = 2, choice = 0;
    Commander(const std::string& file, const std::string& name, SDL_FRect rect);

    virtual ~Commander() = default;
    virtual bool handle();
    virtual void draw();
};

struct Hu final : Commander {
    TextTexture key, value;
    TextButton add, sub;
    Hu();
    bool handle() override;
    void draw() override;
};

struct Li final : Commander {
    Li();
    bool handle() override;
};

#endif //BATTLE_OF_KINMEN_HU_H