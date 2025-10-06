#include "data.h"

FPos toF(const MapPos index) {
    FPos pos = index * GAP + ORIGIN;
    if (index.x % 2) pos.y += GAP.h / 2;
    return pos;
}

MapPos toMap(const FPos pos) {
    FPos index = pos - ORIGIN;
    MapPos xy{};
    xy.x = roundf(index.x / GAP.w);
    if (xy.x % 2) index.y -= GAP.h / 2;
    xy.y = roundf(index.y / GAP.h);
    const FPos center = toF(xy);
    FPos rel = abs(pos - center);
    if (sqrtf(3) * rel.x + rel.y > sqrtf(3) * KM) {
        xy.y += xy.x % 2 - (pos.y < center.y);
        xy.x += pos.x < center.x ? -1 : 1;
    }
    return xy;
}

bool touched(const SDL_FRect r) {
    float x, y;
    SDL_GetMouseState(&x, &y);
    return r.x < x && x < r.x + r.w && r.y < y && y < r.y + r.h;
}