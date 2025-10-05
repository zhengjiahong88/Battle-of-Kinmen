#ifndef BATTLE_OF_KINMEN_BUTTON_H
#define BATTLE_OF_KINMEN_BUTTON_H

#include "base.h"

struct Button {
    virtual ~Button() = default;

    const char* name{};
    virtual void handle() {}
};

struct Single final : Button {
    Single() : Button() { name = "單人遊戲"; }
    void handle() override;
};

struct Create final : Button {
    Create() : Button() { name = "創建房間"; }
    void handle() override;
};

struct Join final : Button {
    Join() : Button() { name = "加入房間"; }
    void handle() override;
};

struct Quit final : Button {
    Quit() : Button() { name = "退出遊戲"; }
    void handle() override {Base::run = false;};
};

#endif //BATTLE_OF_KINMEN_BUTTON_H