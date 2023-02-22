#include "Apple.h"

Apple::Apple(SDL_Window* window) : GameObject(window)
{
    auto renderer = SDL_GetRenderer(window);
    texture = IMG_LoadTexture(renderer, "assets/sprites/apple.png");
    RandomApplePos();
    std::cout << coordinates << std::endl;
}
Apple::~Apple()
{
    ClearApplePos();
}

void Apple::RandomApplePos()
{
    int pos_x = rand() % 28;
    int pos_y = rand() % 16;

    while (GM::GetInstance()->CheckSquare(Vector2<int>{pos_x ,pos_y}) != 0)
    {
        pos_x = rand() % 28;
        pos_y = rand() % 16;
    }

    GM::GetInstance()->SetSquare(Vector2<int> {pos_x, pos_y}, 2);

    position.x = pos_x * GM::GetInstance()->GetSquareSize().x;
    position.y = pos_y * GM::GetInstance()->GetSquareSize().y;

    coordinates.x = pos_x;
    coordinates.y = pos_y;

}

void Apple::ClearApplePos()
{
    GM::GetInstance()->SetSquare(coordinates, 0);
}

void Apple::Render(SDL_Renderer* renderer)
{
    Vector2<float> square_size = GM::GetInstance()->GetSquareSize();

    SDL_Rect texture_rect;
    texture_rect.x = position.x + square_size.x * 0.1f;
    texture_rect.y = position.y + square_size.y * 0.1f;
    texture_rect.w = square_size.x * 0.85f;
    texture_rect.h = square_size.y * 0.85f;

    SDL_RenderCopy(renderer, texture, nullptr, &texture_rect);
}
void Apple::UpdateWindowSize(SDL_Window* window)
{
    SDL_GetWindowSize(window, &window_size.x, &window_size.y);

    position.x = coordinates.x * GM::GetInstance()->GetSquareSize().x;
    position.y = coordinates.y * GM::GetInstance()->GetSquareSize().y;
}