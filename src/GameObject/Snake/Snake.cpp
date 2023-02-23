#include "Snake.h"

Snake::Snake(SDL_Window* window) : GameObject(window)
{
    auto renderer = SDL_GetRenderer(window);
    texture = IMG_LoadTexture(renderer, "assets/sprites/square1.png");


    Create();
}

/// @brief create snake on constructing or recreate for restart 
void Snake::Create()
{
    snake_body.clear();

    int rand_x = rand() % GM::GetInstance()->SIZE_X / 2 + 2;
    int rand_y = rand() % GM::GetInstance()->SIZE_Y;
    snake_body.push_back(Vector2<int> {rand_x, rand_y});
    snake_body.push_back(Vector2<int> {rand_x - 1, rand_y});
    snake_body.push_back(Vector2<int> {rand_x - 2, rand_y});

    for (auto&& i : snake_body)
    {
        GM::GetInstance()->SetSquare(i, 1);
    }

    direction = { 1.f, 0.f };
    new_direction = { 1.f, 0.f };
}

void Snake::Update(double delta_time)
{
    Vector2<float> square_size = GM::GetInstance()->GetSquareSize();
    passed_time += delta_time;

    if (time_between_movements < passed_time)
    {
        passed_time = 0;

        direction = new_direction;

        if (GM::GetInstance()->YouLose(snake_body.front() + direction)) { return; }
        coordinates = snake_body.front() + direction;

        GM::GetInstance()->SetSquare(snake_body.back(), 0);

        prev_tail_coords = snake_body.back();
        snake_body.pop_back();

        snake_body.push_front(coordinates);

        GM::GetInstance()->SetSquare(coordinates, 1);
        GM::GetInstance()->PrintField();
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
                if (direction.y != 1.f) { new_direction = {0.f, -1.f}; }
                break;
            }
            case SDLK_DOWN: {
                if (direction.y != -1.f) { new_direction = {0.f, 1.f}; }
                break;
            }
            case SDLK_LEFT: {
                if (direction.x != 1.f) { new_direction = {-1.f, 0.f}; }
                break;
            }
            case SDLK_RIGHT: {
                if (direction.x != -1.f) { new_direction = {1.f, 0.f}; }
                break;
            }
            case SDLK_w: {
                if (direction.y != 1.f) { new_direction = {0.f, -1.f}; }
                break;
            }
            case SDLK_s: {
                if (direction.y != -1.f) { new_direction = {0.f, 1.f}; }
                break;
            }
            case SDLK_a: {
                if (direction.x != 1.f) { new_direction = {-1.f, 0.f}; }
                break;
            }
            case SDLK_d: {
                if (direction.x != -1.f) { new_direction = {1.f, 0.f}; }
                break;
            }
        }
    }
}

void Snake::IncrementBody(Vector2<int> coords) { snake_body.push_back(snake_body.back()); }

void Snake::ReverseSnake() 
{
    std::list<Vector2<int>> temp(snake_body.end(),snake_body.begin());
    snake_body = temp;
    coordinates = snake_body.front();
    GM::GetInstance()->ClearField();

    new_direction.x = -new_direction.x;
    new_direction.y = -new_direction.y;
}


void Snake::Render(SDL_Renderer* renderer)
{
    
    auto square_size = GM::GetInstance()->GetSquareSize();

    for (auto&& i : snake_body)
    {
        SDL_Rect texture_rect;

        texture_rect.x = (square_size.x * i.x);
        texture_rect.y = (square_size.y * i.y);

        texture_rect.w = square_size.x;
        texture_rect.h = square_size.y;

        SDL_RenderCopy(renderer, texture, nullptr, &texture_rect);
    }

    // auto it = snake_body.begin();
    //  int size = snake_body.size();
    //  float scale = 1.f;
    //  float borderX = square_size.x * 0.0f;
    //  float borderY = square_size.y * 0.0f;
    //  for (int i = 0; i < size; ++i, ++it)
    //  {
    //      if (i == 1)
    //      {
    //          scale = 0.9f;
    //          borderX = square_size.x * 0.05f;
    //          borderY = square_size.y * 0.05f;
    //      }
    //       if (i == size - 2)
    //      {
    //          scale = 0.8f;
    //          borderX = square_size.x * 0.1f;
    //          borderY = square_size.y * 0.1f;
    //      }
    //      else if (i == size - 1)
    //      {
    //          scale = 0.7f;
    //          borderX = square_size.x * 0.15f;
    //          borderY = square_size.y * 0.15f;
    //      }

    //     SDL_Rect texture_rect;

    //     texture_rect.x = (square_size.x * (*it).x) + borderX;
    //     texture_rect.y = (square_size.y * (*it).y) + borderY;

    //     texture_rect.w = square_size.x * scale;
    //     texture_rect.h = square_size.y * scale;

    //     SDL_RenderCopy(renderer, texture, nullptr, &texture_rect);
    // }

}
