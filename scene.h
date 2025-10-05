#ifndef UNTITLED_SCENE_H
#define UNTITLED_SCENE_H

#include <SDL3_image/SDL_image.h>
#include <memory>

#include "base.h"
#include "buttons.h"
#include "Basemap.h"
#include "toggle.h"

struct Scene {
    explicit Scene() = default;
    virtual ~Scene() = default;
    virtual void handle() {}
    virtual void draw() const {}
};

struct Menu final : Scene {
    Single single;
    Create create;
    Join join;
    Quit quit;
    Button* buttonsK[4] = { &single, &create, &join, &quit };
    Buttons buttons;
    FSize size{};
    TextTexture texture;

    explicit Menu();

    void handle() override { buttons.handle(); }

    void draw() const override;
};

struct Field final : Scene {
    const char* k[2] = {"準備完畢", "取消"};
    Toggle toggle;
    SDL_Surface* surface;
    SDL_Texture* texture;
    // Basemap terrain;
    bool paint = false;

    explicit Field() : toggle( { { 1360, 1000 }, { 280, 40 } }, k) {
        surface = IMG_Load("assets/basemap.png");
        texture = SDL_CreateTextureFromSurface(Base::renderer, surface);
        SDL_DestroySurface(surface);
    }

    ~Field() override { SDL_DestroyTexture(texture); }

    void handle() override { toggle.handle(); }

    void draw() const override;
};

struct SceneBase {
    static std::unique_ptr<Menu> menu;
    static std::unique_ptr<Field> field;
    inline static Scene* scene;

    static void init();

    static void menuStart()  { scene = menu.get(); }
    static void fieldStart() { scene = field.get(); }
};

#endif //UNTITLED_SCENE_H