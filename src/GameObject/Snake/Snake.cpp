#include "Snake.h"

Snake::Snake(SDL_Window* window) : GameObject(window)
{
    auto renderer = SDL_GetRenderer(window);
    texture = IMG_LoadTexture(renderer, "assets/sprites/square1.png");


    snake_body.push_back(Vector2<int> {2, 0});
    snake_body.push_back(Vector2<int> {1, 0});

    for (auto&& i : snake_body)
    {
        GM::GetInstance()->SetSquare(i, 1);
    }
}

void Snake::Update(double delta_time)
{
    Vector2<float> square_size = GM::GetInstance()->GetSquareSize();

    passed_time += delta_time;
    if (time_between_movements < passed_time)
    {
        direction = new_direction;
        passed_time = 0;

        if (GM::GetInstance()->YouLose(snake_body.front() + direction)) 
        { 
            return;
        }
        coordinates = snake_body.front() + direction;

        GM::GetInstance()->SetSquare(snake_body.back(), 0);

        prev_tail_coords = snake_body.back();
        snake_body.pop_back();

        snake_body.push_front(coordinates);

        GM::GetInstance()->SetSquare(coordinates, 1);
        GM::GetInstance()->PrintArray();
        return;
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
}

void Snake::IncrementBody(Vector2<int> coords)
{
    snake_body.push_back(snake_body.back());
}

void Snake::Render(SDL_Renderer* renderer)
{
    for (auto&& i : snake_body)
    {
        SDL_Rect texture_rect;
        texture_rect.x = GM::GetInstance()->GetSquareSize().x * i.x;
        texture_rect.y = GM::GetInstance()->GetSquareSize().y * i.y;

        texture_rect.w = GM::GetInstance()->GetSquareSize().x;
        texture_rect.h = GM::GetInstance()->GetSquareSize().y;

        SDL_RenderCopy(renderer, texture, nullptr, &texture_rect);
    }
}
