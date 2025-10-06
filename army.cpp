#include "army.h"

void Army::init(const std::string& name, const std::string& file, const FPos p) {
    pos = p;
    icon.init(name, together(p - size / 2, size), 30, 255);
    icon.initImage(file);
}

void Army::move() {
    const FPos vec = target - pos;
    if (const float len = length(vec); len > 1) pos += vec / len;
}
