#ifndef BATTLE_OF_KINMEN_BUTTON_H
#define BATTLE_OF_KINMEN_BUTTON_H

#include "base.h"
#include "state.h"

struct Button {
    virtual ~Button() = default;

    const char* name{};
    virtual void handle() {}
};

struct Single final : Button {
    Single() : Button() { name = "陳誠"; }
    void handle() override;
};

struct Create final : Button {
    Create() : Button() { name = "胡璉"; }
    void handle() override;
};

struct Join final : Button {
    Join() : Button() { name = "李良榮"; }
    void handle() override;
};

struct Quit final : Button {
    Quit() : Button() { name = "退出遊戲"; }
    void handle() override {Base::run = false;};
};

struct Add final : Button {
    Add() : Button() { name = "+"; }
    void handle() override {State::difficulty++;}
};

struct Sub final : Button {
    Sub() : Button() { name = "-"; }
    void handle() override {State::difficulty--;}
};

#endif //BATTLE_OF_KINMEN_BUTTON_H