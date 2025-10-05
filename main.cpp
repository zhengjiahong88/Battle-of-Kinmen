#include "base.h"
#include "scene.h"

#define WIDTH 1920
#define HEIGHT 1080

int main()
{
    Base base;
    SceneBase::init();

    while (Base::run)
    {
        while (SDL_PollEvent(&Base::event)) {
            if (Base::event.type == SDL_EVENT_QUIT) Base::run = false;
            SceneBase::scene->handle();
        }
        SceneBase::scene->draw();
        SDL_RenderPresent(Base::renderer);
        SDL_Delay(25);
    }
    return 0;
}