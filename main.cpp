#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>

#include "scene.h"

#define WIDTH 1920
#define HEIGHT 1080

int main()
{
    printf("Hello World\n");
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Log("Hello World");

    SDL_Window* window = SDL_CreateWindow("金門保衛戰", WIDTH, HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);

    MainMenu mainMenu(renderer);

    Scene* now = &mainMenu;

    bool run = true;
    while (run)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            run = now->handle(e);
            if (e.type == SDL_EVENT_QUIT) run = false;
        }
        now->draw();
        SDL_RenderPresent(renderer);
        SDL_Delay(25);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}