#include "Field.h"

Field::Field(SDL_Window* window) : GameObject(window)
{
    field.h = window_size.y;
    field.w = window_size.x - (window_size.x / 16) * 2;
    field.x = 0;
    field.y = 0;
    square_size.x = field.w / 28.f;
    square_size.y = field.h / 18.f;
}

void Field::Render(SDL_Renderer* renderer)
{

    SDL_SetRenderDrawColor(renderer, 50, 100, 60, 255);
    SDL_RenderFillRect(renderer, &field);
    SDL_RenderDrawRect(renderer, &field);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    //SDL_Log("%d and %d", field.w, field.h);
    //SDL_Log("%f and %f", square_size.x, square_size.y);
    for (int i = 0; i <= 28; ++i)
    {
        SDL_RenderDrawLineF(renderer, -1 + square_size.x * i, 0, -1 + square_size.x * i, field.h);
        SDL_RenderDrawLineF(renderer, 0 + square_size.x * i, 0, 0 + square_size.x * i, field.h);
        SDL_RenderDrawLineF(renderer, 1 + square_size.x * i, 0, 1 + square_size.x * i, field.h);
    }
    for (int i = 0; i <= 18; ++i)
    {
        SDL_RenderDrawLineF(renderer, 0, -1 + square_size.y * i, field.w, -1 + square_size.y * i);
        SDL_RenderDrawLineF(renderer, 0, 0 + square_size.y * i, field.w, 0 + square_size.y * i);
        SDL_RenderDrawLineF(renderer, 0, 1 + square_size.y * i, field.w, 1 + square_size.y * i);
    }

    SDL_SetRenderDrawColor(renderer, 50, 100, 60, 255);
}
