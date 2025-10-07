#ifndef BATTLE_OF_KINMEN_PLAYER_H
#define BATTLE_OF_KINMEN_PLAYER_H

#include <SDL3/SDL.h>

struct Base {
    static constexpr int WIDTH = 1920;
    static constexpr int HEIGHT = 1080;
    inline static bool run = true;
    inline static SDL_Window* window = nullptr;
    inline static SDL_Renderer* renderer = nullptr;
    inline static SDL_Event event{};
    inline static bool start = false;

    Base();

    ~Base();
};

#endif //BATTLE_OF_KINMEN_PLAYER_H