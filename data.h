#ifndef UNTITLED_DATA_H
#define UNTITLED_DATA_H

#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_rect.h>

struct Pos
{
    Uint16 x, y;
};

struct FPos
{
    float x, y;
};

struct Size
{
    Uint16 w, h;
};

struct FSize
{
    float w, h;
};

struct Rect
{
    Pos pos;
    Size size;

    [[nodiscard]] SDL_FRect toFRect() const { return { static_cast<float>(pos.x), static_cast<float>(pos.y), static_cast<float>(size.w), static_cast<float>(size.h) }; }

    [[nodiscard]] bool inRange(const SDL_MouseMotionEvent &e) const { return pos.x < e.x && e.x < pos.x + size.w && pos.y < e.y && e.y < pos.y + size.h; }
};

inline SDL_FRect toFRect(const FPos p, const FSize s) { return { p.x, p.y, s.w, s.h }; }

inline FPos operator-(const Size& a, const FSize& b) { return { a.w - b.w, a.h - b.h }; }
inline FPos operator/(const FPos& a, const int n) { return { a.x / n, a.y / n }; }
inline FPos operator+(const Pos& a, const FPos& b) { return { a.x + b.x, a.y + b.y }; }

#endif //UNTITLED_DATA_H