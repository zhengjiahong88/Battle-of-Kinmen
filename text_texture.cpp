#include "text_texture.h"

#include "data.h"

SDL_Texture* createTextTexture(FSize& size, SDL_Renderer* renderer, const SDL_Color color, const char* text, const Uint8 font_size)
{
    TTF_Font* font = TTF_OpenFont("standard.ttf", font_size);
    SDL_Surface* surface = TTF_RenderText_Blended(font, text, 0, color);
    TTF_CloseFont(font);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
    float w = 0, h = 0;
    SDL_GetTextureSize(texture, &w, &h);
    size = { w, h };
    return texture;
}

SDL_Texture** createTextTextures(FSize* sizes, SDL_Renderer* renderer, const SDL_Color color, const char** text, const Uint8 size, const Uint8 num)
{
    auto** textures = new SDL_Texture * [num];
    TTF_Font* font = TTF_OpenFont("standard.ttf", size);
    for (int i = 0; i < num; i++)
    {
        SDL_Surface* surface = TTF_RenderText_Blended(font, text[i], 0, color);
        textures[i] = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_DestroySurface(surface);
        float w = 0, h = 0;
        SDL_GetTextureSize(textures[i], &w, &h);
        sizes[i] = { w, h };
    }
    TTF_CloseFont(font);
    return textures;
}

void drawTextTexture(SDL_Renderer* renderer, SDL_Texture* texture, const FSize size, const Rect rect)
{
    SDL_FRect string = toFRect(rect.pos + (rect.size - size) / 2, size);
    SDL_RenderTexture(renderer, texture, nullptr, &string);
}