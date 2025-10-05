#pragma once
#include <SDL3/SDL.h>
#include <cmath>

#include "data.h"

struct Terrain
{
    char symbol;
};

struct Basemap
{
    static constexpr int WIDTH = 44;
    static constexpr int HEIGHT = 38;
    Terrain terrain[HEIGHT][WIDTH]{};
	Basemap();
    static constexpr int KM = 16;
    static constexpr int MAP = 1080;
    static constexpr MapSize FORM = { WIDTH, HEIGHT };
    inline static const FSize GAP = { KM * 1.5, sqrtf(3) * KM };
	inline static const FPos ORIGIN = (MAP - FSize{ 3 * (WIDTH - 1), sqrtf(3) * (2 * HEIGHT - 1) } * KM / 2) / 2;

	Terrain operator[](const MapPos p) const { return terrain[p.y][p.x]; }
	Terrain& operator[](const MapPos p) { return terrain[p.y][p.x]; }

	static SDL_FPoint toSDL(const FPos pos) { return { pos.x, pos.y }; }

    static FPos toF(MapPos index);
	static MapPos toMap(FPos pos);

	static bool inRange(const MapPos p) { return p.x < WIDTH && p.y < HEIGHT; }

	static FPos abs(const FPos p) { return {std::abs(p.x), std::abs(p.y)}; }
};