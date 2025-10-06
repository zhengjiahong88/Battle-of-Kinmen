#pragma once

#include "data.h"

struct Terrain
{
    char symbol;
};

struct Basemap
{
    Terrain terrain[HEIGHT][WIDTH]{};
	Basemap();
	Terrain operator[](const MapPos p) const { return terrain[p.y][p.x]; }
	Terrain& operator[](const MapPos p) { return terrain[p.y][p.x]; }
};