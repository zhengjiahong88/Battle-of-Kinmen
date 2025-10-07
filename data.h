#ifndef UNTITLED_DATA_H
#define UNTITLED_DATA_H

#include <cmath>
#include <string>

#include "base.h"

struct Pos { Uint16 x, y; };

struct FPos { float x, y; };

struct Size { Uint16 w, h; };

struct FSize { float w, h; };

struct MapPos { Uint8 x, y; };

struct MapSize { Uint8 w, h; };

inline FPos operator-(const Size a, const FSize b) { return { a.w - b.w, a.h - b.h }; }
inline FPos operator/(const FPos a, const int n) { return { a.x / n, a.y / n }; }
inline FPos operator+(const Pos a, const FPos b) { return { a.x + b.x, a.y + b.y }; }
inline FSize operator*(const FSize a, const int n) { return { a.w * n, a.h * n }; }
inline FSize operator*(const MapPos a, const FSize b) { return {a.x * b.w, a.y * b.h}; }
inline FPos operator+(const FSize a, const FPos b) { return {a.w + b.x, a.h + b.y}; }
inline FPos operator-(const FPos a, const FPos b) { return {a.x - b.x, a.y - b.y}; }
inline FSize operator/(const FSize a, const int n) { return { a.w / n, a.h / n }; }
inline FPos operator-(const int n, const FSize a) { return { n - a.w, n - a.h }; }
inline FPos operator*(const FPos a, const int n) { return { a.x * n, a.y * n}; }
inline FPos operator+(const FPos a, const FPos b) { return {a.x + b.x, a.y + b.y}; }
inline FSize operator-(const FSize a, const FSize b) { return {a.w - b.w, a.h - b.h}; }
inline FPos operator-(const FPos a, const FSize b) { return {a.x - b.w, a.y - b.h}; }
inline FPos operator/(const FPos a, const float n) { return { a.x / n, a.y / n }; }
inline void operator+=(Pos& a, const Size b) { a.x += b.w; a.y += b.h; }
inline void operator+=(FPos& a, const FPos b) { a.x += b.x; a.y += b.y; }

static constexpr int WIDTH = 44;
static constexpr int HEIGHT = 38;
static constexpr int KM = 16;
static constexpr int MAP = 1080;
static constexpr MapSize FORM = { WIDTH, HEIGHT };
inline static const FSize GAP = { KM * 1.5, sqrtf(3) * KM };
inline static const FPos ORIGIN = (MAP - FSize{ 3 * (WIDTH - 1), sqrtf(3) * (2 * HEIGHT - 1) } * KM / 2) / 2;

static SDL_FPoint toSDL(const FPos pos) { return { pos.x, pos.y }; }

static FPos toPos(const SDL_FRect r) { return {r.x, r.y};}
static FSize toSize(const SDL_FRect r) { return {r.w, r.h};}
static SDL_FRect together(const FPos pos, const FSize size) { return { pos.x, pos.y, size.w, size.h }; }

FPos toF(MapPos index);
MapPos toMap(FPos pos);

bool touched(SDL_FRect r);
static bool inRange(const MapPos p) { return p.x < WIDTH && p.y < HEIGHT; }

static FPos abs(const FPos p) { return {std::abs(p.x), std::abs(p.y)}; }

static float length(const FPos p) { return std::sqrt(p.x * p.x + p.y * p.y); }

static std::string to_string(const MapPos pos) { return std::to_string(pos.x) + " " + std::to_string(pos.y); }

#endif //UNTITLED_DATA_H