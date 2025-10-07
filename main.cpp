#include "base.h"
#include "commander.h"

#define WIDTH 1920
#define HEIGHT 1080

int main()
{
    Base base;
    ImageTexture basemap;
    basemap.init("basemap");
    TextTexture title;
    TextTexture hint;
    title.init("古寧頭戰役", 60, 255);
    hint.init("請選擇欲扮演的人物", 40, 255);
    Hu hu;
    Li li;
    Commander *commander = nullptr;

    while (Base::run)
    {
        while (SDL_PollEvent(&Base::event)) {
            if (Base::event.type == SDL_EVENT_QUIT) Base::run = false;
            if (!commander) {
                if (hu.headshot.handle()) commander = &hu;
                if (li.headshot.handle()) commander = &li;
            } else if (!Base::start) commander->handle();
        }
        basemap.draw({0, 0, WIDTH, HEIGHT});
        title.draw({1080, 60, 840, 120});
        if (!commander) {
            hint.draw({1080, 240, 840, 40});
            hu.headshot.draw();
            li.headshot.draw();
        } else if (!Base::start) commander->draw();
        SDL_RenderPresent(Base::renderer);
        SDL_Delay(25);
    }
    return 0;
}
