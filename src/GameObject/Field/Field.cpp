// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Field.h"

#include "GameManager/GameManager.h"

Field::Field()
{
    field.w = GameManager::GetInstance().SIZE_X * GameManager::GetInstance().GetSquareSize().x;
    field.h = GameManager::GetInstance().SIZE_Y * GameManager::GetInstance().GetSquareSize().y;
}

Field::~Field()
{
    std::cout << "FIELD DESTRUCTOR" << std::endl;
}

void Field::Render(SDL_Renderer* renderer)
{
    // draw rect as background for grid
    SDL_SetRenderDrawColor(renderer, 15, 15, 15, 255);
    SDL_RenderFillRect(renderer, &field);
    SDL_RenderDrawRect(renderer, &field);
    // starts drawing grid
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    Vector2<float> square_size = GameManager::GetInstance().GetSquareSize();
    for (int i = 0; i <= GameManager::GetInstance().SIZE_X; ++i)
    {
        SDL_RenderDrawLineF(renderer, -1 + square_size.x * i, 0, -1 + square_size.x * i, field.h);
        SDL_RenderDrawLineF(renderer, 0 + square_size.x * i, 0, 0 + square_size.x * i, field.h);
        SDL_RenderDrawLineF(renderer, 1 + square_size.x * i, 0, 1 + square_size.x * i, field.h);
    }
    for (int i = 0; i <= GameManager::GetInstance().SIZE_Y; ++i)
    {
        SDL_RenderDrawLineF(renderer, 0, -1 + square_size.y * i, field.w, -1 + square_size.y * i);
        SDL_RenderDrawLineF(renderer, 0, 0 + square_size.y * i, field.w, 0 + square_size.y * i);
        SDL_RenderDrawLineF(renderer, 0, 1 + square_size.y * i, field.w, 1 + square_size.y * i);
    }
    SDL_SetRenderDrawColor(renderer, 15, 15, 15, 255);
}
