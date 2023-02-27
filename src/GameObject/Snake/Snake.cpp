#include "Snake.h"

Snake::Snake(SDL_Window* window) : GameObject(window)
{
    auto renderer = SDL_GetRenderer(window);
    head_t = IMG_LoadTexture(renderer, "assets/sprites/square_head.png");
    body_t = IMG_LoadTexture(renderer, "assets/sprites/square_body.png");
}

Snake::~Snake()
{
    SDL_DestroyTexture(head_t);
    head_t = nullptr;
    SDL_DestroyTexture(body_t);
    body_t = nullptr;
}

/// @brief Create snake for new game
/// @param difficulty set speed of snake, depends on difficulty lvl
void Snake::Create(const DIFFICULTY_ difficulty = DIFFICULTY_NORMAL)
{
    snake_body.clear();

    int rand_x = rand() % Game_Manager::GetInstance()->SIZE_X / 2 + 2;
    int rand_y = rand() % Game_Manager::GetInstance()->SIZE_Y;

    snake_body.emplace_back(Vector2<int> {rand_x, rand_y});
    snake_body.emplace_back(Vector2<int> {rand_x - 1, rand_y});
    snake_body.emplace_back(Vector2<int> {rand_x - 2, rand_y});

    for (auto&& i : snake_body)
    {
        Game_Manager::GetInstance()->SetSquare(i, 1);
    }

    move_type = MOVE_TYPE_NORMAL;
    direction = {1, 0};
    new_direction = {1, 0};
    time_between_movements = difficulty / 100.f;
}

void Snake::Update(double delta_time)
{
    Vector2<float> square_size = Game_Manager::GetInstance()->GetSquareSize();

    passed_time += delta_time;

    if (time_between_movements < passed_time)
    {
        passed_time = 0;
        direction = new_direction;

        switch (move_type)
        {
            case MOVE_TYPE_NORMAL: {
                if (Game_Manager::GetInstance()->CheckLose(snake_body.front() + direction)) { return; }
                coordinates = snake_body.front() + direction;
                Game_Manager::GetInstance()->SetSquare(snake_body.back(), 0);

                prev_tail_coords = snake_body.back();
                snake_body.pop_back();

                snake_body.emplace_front(coordinates);
                Game_Manager::GetInstance()->SetSquare(coordinates, 1);
                break;
            }
            case MOVE_TYPE_REVERSED: {
                if (Game_Manager::GetInstance()->CheckLose(snake_body.back() + direction)) { return; }
                coordinates = snake_body.back() + direction;
                Game_Manager::GetInstance()->SetSquare(snake_body.front(), 0);

                prev_tail_coords = snake_body.front();
                snake_body.pop_front();

                snake_body.emplace_back(coordinates);
                Game_Manager::GetInstance()->SetSquare(coordinates, 1);
                break;
            }
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
                if (direction.y != 1) { new_direction = {0, -1}; }
                break;
            }
            case SDLK_DOWN: {
                if (direction.y != -1) { new_direction = {0, 1}; }
                break;
            }
            case SDLK_LEFT: {
                if (direction.x != 1) { new_direction = {-1, 0}; }
                break;
            }
            case SDLK_RIGHT: {
                if (direction.x != -1) { new_direction = {1, 0}; }
                break;
            }
            case SDLK_w: {
                if (direction.y != 1) { new_direction = {0, -1}; }
                break;
            }
            case SDLK_s: {
                if (direction.y != -1) { new_direction = {0, 1}; }
                break;
            }
            case SDLK_a: {
                if (direction.x != 1) { new_direction = {-1, 0}; }
                break;
            }
            case SDLK_d: {
                if (direction.x != -1) { new_direction = {1, 0}; }
                break;
            }
        }
    }
}

void Snake::IncrementBody()
{
    if (move_type == MOVE_TYPE_NORMAL) { snake_body.push_back(snake_body.back()); }
    else { snake_body.push_front(snake_body.front()); }
}

void Snake::ReverseSnake()
{

    if (move_type == MOVE_TYPE_NORMAL)
    {
        move_type = MOVE_TYPE_REVERSED;
        coordinates = snake_body.back();
    }
    else
    {
        move_type = MOVE_TYPE_NORMAL;
        coordinates = snake_body.front();
    }
    direction = new_direction = prev_tail_coords - coordinates;
}

void Snake::Render(SDL_Renderer* renderer)
{

    auto square_size = Game_Manager::GetInstance()->GetSquareSize();
    if (move_type == MOVE_TYPE_NORMAL)
    {
        auto i = snake_body.begin();
        auto k = snake_body.end();
        for (; i != k; ++i)
        {
            SDL_Rect texture_rect;
            texture_rect.x = (square_size.x * (*i).x);
            texture_rect.y = (square_size.y * (*i).y);
            texture_rect.w = square_size.x;
            texture_rect.h = square_size.y;
            if (i == snake_body.begin()) { SDL_RenderCopy(renderer, head_t, nullptr, &texture_rect); }
            else { SDL_RenderCopy(renderer, body_t, nullptr, &texture_rect); }
        }
    }
    else
    {
        auto i = snake_body.rbegin();
        auto k = snake_body.rend();

        for (; i != snake_body.rend(); ++i)
        {
            SDL_Rect texture_rect;
            texture_rect.x = (square_size.x * (*i).x);
            texture_rect.y = (square_size.y * (*i).y);
            texture_rect.w = square_size.x;
            texture_rect.h = square_size.y;
            if (i == snake_body.rbegin()) { SDL_RenderCopy(renderer, head_t, nullptr, &texture_rect); }
            else { SDL_RenderCopy(renderer, body_t, nullptr, &texture_rect); }
        }
    }
}
