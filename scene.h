#ifndef UNTITLED_SCENE_H
#define UNTITLED_SCENE_H

#include <SDL3_image/SDL_image.h>
#include <memory>

#include "buttons.h"
#include "basemap.h"
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
    SDL_Texture *hu, *li;
    TextTexture title, hint, hut, lit;
    Button *buttonsK[4] = { &single, &create, &join, &quit };
    Buttons buttons;
    FSize size{};
    SDL_FRect HU_RECT{384, 312, 384, 512};
    SDL_FRect LI_RECT{1152, 312, 384, 512};

    explicit Menu();

    ~Menu() override;

    void handle() override;

    void draw() const override;
};

struct Field final : Scene {
    Add add;
    Sub sub;
    Button *buttonsK[2] = {&add, &sub};
    Buttons buttons;
    const char* k[2] = {"準備完畢", "取消"};
    Toggle toggle;
    SDL_Texture* texture;
    TextTexture key, value;
    // Basemap terrain;
    bool paint = false;

    explicit Field();

    ~Field() override { SDL_DestroyTexture(texture); }

    void handle() override;

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