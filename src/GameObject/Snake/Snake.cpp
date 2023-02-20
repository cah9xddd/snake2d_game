#include "Snake.h"

Snake::Snake(SDL_Window* window) : GameObject(window)
{
    auto renderer = SDL_GetRenderer(window);
    texture = IMG_LoadTexture(renderer, "assets/sprites/apple.png");
}

Snake::~Snake()
{
}

void Snake::Render(SDL_Renderer* renderer)
{
    SDL_Rect texture_rect;
    texture_rect.x = 5;
    texture_rect.y = 5;
    texture_rect.w = window_size.x / 42.f;
    texture_rect.h = window_size.y / 24.f;
    SDL_RenderCopy(renderer, texture, nullptr, &texture_rect);
}
