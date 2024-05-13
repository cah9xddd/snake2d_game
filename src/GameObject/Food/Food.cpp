// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Food.h"

#include "GameManager/GameManager.h"

Food::Food(SDL_Renderer* renderer)
{
    food_texture         = IMG_LoadTexture(renderer, "assets/sprites/apple.png");
    reverse_food_texture = IMG_LoadTexture(renderer, "assets/sprites/reverse.png");
}

Food::~Food()
{
    std::cout << "FOOD DESTRUCTOR" << std::endl;
    SDL_DestroyTexture(food_texture);
    food_texture = nullptr;
    SDL_DestroyTexture(reverse_food_texture);
    reverse_food_texture = nullptr;
}

void Food::CreateNewFood()
{
    int pos_x = rand() % GameManager::GetInstance().SIZE_X;
    int pos_y = rand() % GameManager::GetInstance().SIZE_Y;

    while (GameManager::GetInstance().CheckSquare(Vector2<int> { pos_x, pos_y }) != 0)
    {
        pos_x = rand() % GameManager::GetInstance().SIZE_X;
        pos_y = rand() % GameManager::GetInstance().SIZE_Y;
    }

    GameManager::GetInstance().SetSquare(Vector2<int> { pos_x, pos_y }, 2);

    coordinates.x = pos_x;
    coordinates.y = pos_y;

    scale     = 1.1f;
    border    = -0.05f;
    shrinking = true;

    int rand_t = rand() % 4;
    if (rand_t != 3) { type = FOOD_TYPE_NORMAL; }
    else { type = FOOD_TYPE_REVERSE; }
}

Food::FOOD_TYPE_ Food::GetFoodType() const
{
    return type;
}

Vector2<int> Food::GetCoordinates()
{
    return coordinates;
}

void Food::Render(SDL_Renderer* renderer)
{
    Vector2<float> square_size = GameManager::GetInstance().GetSquareSize();

    SDL_Rect texture_rect;
    texture_rect.x = (coordinates.x * square_size.x) + (square_size.x * border);
    texture_rect.y = (coordinates.y * square_size.y) + (square_size.y * border);
    texture_rect.w = square_size.x * scale;
    texture_rect.h = square_size.y * scale;
    if (type == FOOD_TYPE_NORMAL) { SDL_RenderCopy(renderer, food_texture, nullptr, &texture_rect); }
    else { SDL_RenderCopy(renderer, reverse_food_texture, nullptr, &texture_rect); }
}

void Food::Update(std::chrono::milliseconds delta_time)
{
    if (shrinking)
    {
        scale -= delta_time.count() / 4000.f;
        border += delta_time.count() / 8000.f;
    }
    else
    {
        scale += delta_time.count() / 4000.f;
        border -= delta_time.count() / 8000.f;
    }

    if (scale < 0.8f || scale > 1.1f) { shrinking = !shrinking; }
}