#include "Snake.h"

Snake::Snake(SDL_Window* window) : GameObject(window)
{
    auto renderer = SDL_GetRenderer(window);
    texture = IMG_LoadTexture(renderer, "assets/sprites/square1.png");
    speed = window_size.x / 8;
    GM::GetInstance()->SetSquare(0, 0, 1);
    head_pos = {0, 0};
}

void Snake::Update(double delta_time)
{
    //std::cout << delta_time << std::endl;
    std::cout << position << std::endl;
    Vector2<float> velocity = direction * speed;
    Vector2<float> square_size = GM::GetInstance()->GetSquareSize();

    position = position + (velocity * delta_time);

    if (new_direction.y != 0.f)
    {
        int i = ((int)position.x % (int)square_size.x);
        if (i <= 1.f || i >= square_size.x - 1.f)
        {
            direction = new_direction;
            return;
        }
    }
    else if (new_direction.x != 0.f)
    {
        int i = ((int)position.y % (int)square_size.y);
        if (i <= 1.f || i >= square_size.y - 1.f)
        {
            direction = new_direction;
            return;
        }
    }
}


void Snake::HandleInput(SDL_Event& event)
{
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
    {
        switch (event.key.keysym.sym)
        {
            case SDLK_UP: {
                if (direction.y != 1.f)
                {
                    new_direction = {0.f, -1.f};
                }
                break;
            }
            case SDLK_DOWN: {
                if (direction.y != -1.f)
                {
                    new_direction = {0.f, 1.f};
                }
                break;
            }
            case SDLK_LEFT: {
                if (direction.x != 1.f)
                {
                    new_direction = {-1.f, 0.f};
                }
                break;
            }
            case SDLK_RIGHT: {
                if (direction.x != -1.f)
                {
                    new_direction = {1.f, 0.f};
                }
            }
            break;
        }
    }
}

void Snake::UpdateWindowSize(SDL_Window* window)
{
    SDL_GetWindowSize(window, &window_size.x, &window_size.y);

    speed = window_size.x / 8;
}

void Snake::Render(SDL_Renderer* renderer)
{
    SDL_Rect texture_rect;
    texture_rect.x = position.x;
    texture_rect.y = position.y;
    texture_rect.w = GM::GetInstance()->GetSquareSize().x;
    texture_rect.h = GM::GetInstance()->GetSquareSize().y;
    SDL_RenderCopy(renderer, texture, nullptr, &texture_rect);
}
