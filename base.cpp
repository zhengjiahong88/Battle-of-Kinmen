#include "base.h"
#include <SDL3_ttf/SDL_ttf.h>

Base::Base() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    window = SDL_CreateWindow("金門保衛戰", WIDTH, HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, nullptr);
    run = true;
}

Base::~Base() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}