#include "Food.h"

Food::Food(SDL_Window* window) : GameObject(window)
{
    auto renderer = SDL_GetRenderer(window);
    texture1 = IMG_LoadTexture(renderer, "assets/sprites/triangle.png");
    texture2 = IMG_LoadTexture(renderer, "assets/sprites/reverse.png");
    RandomApplePos();
}
Food::~Food() {
    SDL_DestroyTexture(texture1);
    texture1 = nullptr;
    SDL_DestroyTexture(texture2);
    texture2 = nullptr;
}

void Food::RandomApplePos()
{
    int pos_x = rand() % 28;
    int pos_y = rand() % 18;

    while (GM::GetInstance()->CheckSquare(Vector2<int> {pos_x, pos_y}) != 0)
    {
        pos_x = rand() % 28;
        pos_y = rand() % 18;
    }

    GM::GetInstance()->SetSquare(Vector2<int> {pos_x, pos_y}, 2);

    coordinates.x = pos_x;
    coordinates.y = pos_y;

    scale = 1.4f;
    border = -0.2f;

    int rand_t = rand() % 4;
    if (rand_t != 3)
    {
        type = FOOD_TYPE_NORMAL;
    }
    else { type = FOOD_TYPE_REVERSE; }
}

void Food::Render(SDL_Renderer* renderer)
{
    Vector2<float> square_size = GM::GetInstance()->GetSquareSize();

    SDL_Rect texture_rect;
    texture_rect.x = (coordinates.x * square_size.x) + (square_size.x * border);
    texture_rect.y = (coordinates.y * square_size.y) + (square_size.y * border);
    texture_rect.w = square_size.x * scale;
    texture_rect.h = square_size.y * scale;
    if (type == FOOD_TYPE_NORMAL) { SDL_RenderCopy(renderer, texture1, nullptr, &texture_rect); }
    else { SDL_RenderCopy(renderer, texture2, nullptr, &texture_rect); }
}
void Food::Update(double delta_time)
{
    if (scale > 1.0f)
    {
        scale -= 0.01f;
        border += 0.005f;
    }
}
void Food::UpdateWindowSize(SDL_Window* window)
{
    SDL_GetWindowSize(window, &window_size.x, &window_size.y);

    position.x = coordinates.x * GM::GetInstance()->GetSquareSize().x;
    position.y = coordinates.y * GM::GetInstance()->GetSquareSize().y;
}