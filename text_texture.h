#ifndef UNTITLED_TEXT_TEXTURE_H
#define UNTITLED_TEXT_TEXTURE_H

#include <SDL3_ttf/SDL_ttf.h>

#include "data.h"

SDL_Texture* createTextTexture(FSize& size, SDL_Renderer* renderer, SDL_Color color, const char* text, Uint8 font_size);

SDL_Texture** createTextTextures(FSize* sizes, SDL_Renderer* renderer, SDL_Color color, const char** text, Uint8 size, Uint8 num);

void drawTextTexture(SDL_Renderer* renderer, SDL_Texture* texture, FSize size, Rect rect);

#endif //UNTITLED_TEXT_TEXTURE_H