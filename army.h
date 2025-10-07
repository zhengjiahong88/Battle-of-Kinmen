#ifndef BATTLE_OF_KINMEN_ARMY_H
#define BATTLE_OF_KINMEN_ARMY_H

#include "button.h"

struct Army {
    inline static FSize size{24.f, 18.f};
    ImageButton icon;
    FPos pos{};
    FPos target{};
    std::string arms;
    int hp = 1728, fire = 144, protection = 12;

    void init(const std::string& name, const std::string& arms, FPos p);
    void move();
};

#endif //BATTLE_OF_KINMEN_ARMY_H
