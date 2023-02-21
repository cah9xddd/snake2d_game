#include "Snake.h"

Snake::Snake(SDL_Window* window) : GameObject(window)
{
    auto renderer = SDL_GetRenderer(window);
    texture = IMG_LoadTexture(renderer, "assets/sprites/snake_sprites.png");

}

Snake::~Snake()
{
}

void Snake::Update()
{
    
}

void Snake::Render(SDL_Renderer* renderer)
{
    SDL_Rect texture_rect;
    texture_rect.x = 0;
    texture_rect.y = 0;
    texture_rect.w = 400;  // GM::GetInstance()->GetSquareSize().x;
    texture_rect.h = 400;  // GM::GetInstance()->GetSquareSize().y;
    SDL_RenderCopy(renderer, texture, nullptr, &texture_rect);
}
