#ifndef BATTLE_OF_KINMEN_TOGGLE_H
#define BATTLE_OF_KINMEN_TOGGLE_H

#include "data.h"
#include "texture.h"

struct Toggle {
    Rect rect;
    bool down = false;
    bool touch = false;
    bool index = false;
    TextTexture textures[2];
    const char **texts;

    Toggle(Rect rect, const char *texts[2]);

    bool handle();

    void draw() const;
};

#endif //BATTLE_OF_KINMEN_TOGGLE_H