#include "Apple.h"

Apple::Apple(SDL_Window* window) : GameObject(window)
{
    auto renderer = SDL_GetRenderer(window);
    texture = IMG_LoadTexture(renderer, "assets/sprites/apple.png");
    RandomApplePos();
    std::cout << position.x << " " << position.y << std::endl;
}

Apple::~Apple()
{
    ClearApplePos();
}

void Apple::RandomApplePos()
{
    Uint32 pos_x = rand() % 28;
    Uint32 pos_y = rand() % 18;
    while (GM::GetInstance()->CheckSquare(pos_x, pos_y) != 0)
    {
        Uint32 pos_x = rand() % 28;
        Uint32 pos_y = rand() % 18;
    }
    GM::GetInstance()->SetSquare(pos_x,pos_y,2);
    position.x = 5 + pos_x * GM::GetInstance()->GetSquareSize().x;
    position.y = 5 + pos_y * GM::GetInstance()->GetSquareSize().y;
    coordinates.x = pos_x;
    coordinates.y = pos_y;
}

void Apple::ClearApplePos()
{
    GM::GetInstance()->SetSquare(coordinates.x,coordinates.y, 0);
}

void Apple::Render(SDL_Renderer* renderer)
{
    SDL_Rect texture_rect;
    texture_rect.x = position.x;
    texture_rect.y = position.y;
    texture_rect.w = window_size.x / 42.f;
    texture_rect.h = window_size.y / 24.f;
    SDL_RenderCopy(renderer, texture, nullptr, &texture_rect);
}
