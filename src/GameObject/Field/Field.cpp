#include "Field.h"

Field::Field(SDL_Window *window) : GameObject(window) { UpdateWindowSize(window); }

void Field::Render(SDL_Renderer *renderer)
{
    // draw rect as background for grid
    SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
    SDL_RenderFillRect(renderer, &field);
    SDL_RenderDrawRect(renderer, &field);
    // starts drawing grid
    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
    Vector2<float> square_size = GameManager::GetInstance()->GetSquareSize();
    for (int i = 0; i <= GameManager::GetInstance()->SIZE_X; ++i)
    {
        SDL_RenderDrawLineF(renderer, -1 + square_size.x * i, 0, -1 + square_size.x * i, field.h);
        SDL_RenderDrawLineF(renderer, 0 + square_size.x * i, 0, 0 + square_size.x * i, field.h);
        SDL_RenderDrawLineF(renderer, 1 + square_size.x * i, 0, 1 + square_size.x * i, field.h);
    }
    for (int i = 0; i <= GameManager::GetInstance()->SIZE_X; ++i)
    {
        SDL_RenderDrawLineF(renderer, 0, -1 + square_size.y * i, field.w, -1 + square_size.y * i);
        SDL_RenderDrawLineF(renderer, 0, 0 + square_size.y * i, field.w, 0 + square_size.y * i);
        SDL_RenderDrawLineF(renderer, 0, 1 + square_size.y * i, field.w, 1 + square_size.y * i);
    }
    SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
}

void Field::UpdateWindowSize(SDL_Window *window)
{
    SDL_GetWindowSize(window, &window_size.x, &window_size.y);

    field.w = GameManager::GetInstance()->SIZE_X * GameManager::GetInstance()->GetSquareSize().x;
    field.h = GameManager::GetInstance()->SIZE_Y * GameManager::GetInstance()->GetSquareSize().y;
}
