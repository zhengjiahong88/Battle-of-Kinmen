#ifndef UNTITLED_SCENE_H
#define UNTITLED_SCENE_H

#include "buttons.h"

struct Scene {
    virtual ~Scene() = default;
    [[nodiscard]] virtual bool handle(const SDL_Event& e) = 0;
    virtual void draw() const = 0;
};

struct MainMenu final : Scene {
    SDL_Renderer* renderer;
    Buttons buttons;
    FSize size{};
    SDL_Texture* texture;
    const char* k[4] = { "單人遊戲", "創建房間", "加入房間", "退出遊戲" };
    explicit MainMenu(SDL_Renderer* renderer) : renderer(renderer), buttons( { { 640, 360 }, { 640, 90 } }, 180, 4, k, renderer) { texture = createTextTexture(size, renderer, { 255, 255, 255, 255 }, "金門保衛戰", 120); }
    ~MainMenu() override { SDL_DestroyTexture(texture); }
    [[nodiscard]] bool handle(const SDL_Event& e) override {
        switch (buttons.handle(e)) {
            case 0: SDL_Log("單人遊戲"); break;
            case 1: SDL_Log("創建房間"); break;
            case 2: SDL_Log("加入房間"); break;
            case 3: return false;
            default: ;
        }
        return true;
    }

    void draw() const override {
        drawTextTexture(renderer, texture, size, { { 0, 0 }, { 1920, 360 } });
        buttons.draw();
    }
};

#endif //UNTITLED_SCENE_H