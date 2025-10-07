#pragma once

#include "data.h"

struct Basemap
{
    char terrain[HEIGHT][WIDTH]{};
	Basemap();
	char operator[](const MapPos p) const { return terrain[p.y][p.x]; }
	char& operator[](const MapPos p) { return terrain[p.y][p.x]; }
};