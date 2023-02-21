#include "Snake.h"

Snake::Snake(SDL_Window* window) : GameObject(window)
{
    auto renderer = SDL_GetRenderer(window);
    texture = IMG_LoadTexture(renderer, "assets/sprites/square1.png");

    GM::GetInstance()->SetSquare(0, 0, 1);

    snake_body.push_back(Vector2<int>(0, 0));
}

void Snake::Update(double delta_time)
{
    Vector2<float> square_size = GM::GetInstance()->GetSquareSize();

    passed_time += delta_time;
    if (time_between_movements < passed_time)
    {
        passed_time = 0;
        position = position + (direction * square_size);
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
                    direction = {0.f, -1.f};
                }
                break;
            }
            case SDLK_DOWN: {
                if (direction.y != -1.f)
                {
                    direction = {0.f, 1.f};
                }
                break;
            }
            case SDLK_LEFT: {
                if (direction.x != 1.f)
                {
                    direction = {-1.f, 0.f};
                }
                break;
            }
            case SDLK_RIGHT: {
                if (direction.x != -1.f)
                {
                    direction = {1.f, 0.f};
                }
            }
            break;
        }
    }
}

void Snake::UpdateWindowSize(SDL_Window* window)
{
    SDL_GetWindowSize(window, &window_size.x, &window_size.y);
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
