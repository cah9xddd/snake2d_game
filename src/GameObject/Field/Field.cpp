#include "Field.h"

Field::Field(SDL_Window* window) : GameObject(window)
{
    UpdateWindowSize(window);
}

void Field::Render(SDL_Renderer* renderer)
{

    SDL_SetRenderDrawColor(renderer, 0, 120, 160, 255);
    //SDL_SetRenderDrawColor(renderer, 60, 60, 60, 255);
    SDL_RenderFillRect(renderer, &field);
    SDL_RenderDrawRect(renderer, &field);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    Vector2<float> square_size = GM::GetInstance()->GetSquareSize();
    for (int i = 0; i <= GM::GetInstance()->SIZE_X; ++i)
    {
        SDL_RenderDrawLineF(renderer, -1 + square_size.x * i, 0, -1 + square_size.x * i, field.h);
        SDL_RenderDrawLineF(renderer, 0 + square_size.x * i, 0, 0 + square_size.x * i, field.h);
        SDL_RenderDrawLineF(renderer, 1 + square_size.x * i, 0, 1 + square_size.x * i, field.h);
    }
    for (int i = 0; i <= GM::GetInstance()->SIZE_X; ++i)
    {
        SDL_RenderDrawLineF(renderer, 0, -1 + square_size.y * i, field.w, -1 + square_size.y * i);
        SDL_RenderDrawLineF(renderer, 0, 0 + square_size.y * i, field.w, 0 + square_size.y * i);
        SDL_RenderDrawLineF(renderer, 0, 1 + square_size.y * i, field.w, 1 + square_size.y * i);
    }

    SDL_SetRenderDrawColor(renderer, 0, 120, 160, 255);
   // SDL_SetRenderDrawColor(renderer, 60, 60, 60, 255);
}

void Field::UpdateWindowSize(SDL_Window* window)
{
    SDL_GetWindowSize(window, &window_size.x, &window_size.y);

    field.w = GM::GetInstance()->SIZE_X * GM::GetInstance()->GetSquareSize().x;
    field.h = GM::GetInstance()->SIZE_Y * GM::GetInstance()->GetSquareSize().y;

    field.x = 0;
    field.y = 0;
}
