#include "Snake.h"

Snake::Snake(SDL_Renderer* renderer)
{
    head_texture = IMG_LoadTexture(renderer, "assets/sprites/square_head.png");
    body_texture = IMG_LoadTexture(renderer, "assets/sprites/square_body.png");
}

Snake::~Snake()
{
    std::cout << "SNAKE DESTRUCTOR" << std::endl;
    SDL_DestroyTexture(head_texture);
    head_texture = nullptr;
    SDL_DestroyTexture(body_texture);
    body_texture = nullptr;
}

/// @brief Create snake for new game
/// @param difficulty set speed of snake, depends on difficulty lvl
void Snake::Create(const DIFFICULTY_ difficulty = DIFFICULTY_NORMAL)
{
    snake_body.clear();

    int rand_x = rand() % GameManager::GetInstance().SIZE_X / 2 + 2;
    int rand_y = rand() % GameManager::GetInstance().SIZE_Y;

    snake_body.emplace_back(rand_x, rand_y);
    snake_body.emplace_back(rand_x - 1, rand_y);
    snake_body.emplace_back(rand_x - 2, rand_y);

    for (auto&& i : snake_body) { GameManager::GetInstance().SetSquare(i, 1); }

    move_type     = MOVE_TYPE_NORMAL;
    direction     = Vector2<int>(1, 0);
    new_direction = Vector2<int>(1, 0);

    time_between_movements = std::chrono::milliseconds(difficulty);
}

void Snake::Update(std::chrono::milliseconds delta_time)
{
    Vector2<float> square_size = GameManager::GetInstance().GetSquareSize();

    passed_time += delta_time;

    if (time_between_movements < passed_time)
    {
        passed_time = std::chrono::milliseconds(0);
        direction   = new_direction;

        switch (move_type)
        {
            case MOVE_TYPE_NORMAL : {
                if (GameManager::GetInstance().CheckLose(snake_body.front() + direction)) { return; }
                head_coordinates = snake_body.front() + direction;
                GameManager::GetInstance().SetSquare(snake_body.back(), 0);

                prev_tail_coordinates = snake_body.back();
                snake_body.pop_back();

                snake_body.emplace_front(head_coordinates);
                GameManager::GetInstance().SetSquare(head_coordinates, 1);
                break;
            }
            case MOVE_TYPE_REVERSED : {
                if (GameManager::GetInstance().CheckLose(snake_body.back() + direction)) { return; }
                head_coordinates = snake_body.back() + direction;
                GameManager::GetInstance().SetSquare(snake_body.front(), 0);

                prev_tail_coordinates = snake_body.front();
                snake_body.pop_front();

                snake_body.emplace_back(head_coordinates);
                GameManager::GetInstance().SetSquare(head_coordinates, 1);
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
            case SDLK_UP : {
                if (direction.y != 1) { new_direction = Vector2<int>(0, -1); }
                break;
            }
            case SDLK_DOWN : {
                if (direction.y != -1) { new_direction = Vector2<int>(0, 1); }
                break;
            }
            case SDLK_LEFT : {
                if (direction.x != 1) { new_direction = Vector2<int>(-1, 0); }
                break;
            }
            case SDLK_RIGHT : {
                if (direction.x != -1) { new_direction = Vector2<int>(1, 0); }
                break;
            }
            case SDLK_w : {
                if (direction.y != 1) { new_direction = Vector2<int>(0, -1); }
                break;
            }
            case SDLK_s : {
                if (direction.y != -1) { new_direction = Vector2<int>(0, 1); }
                break;
            }
            case SDLK_a : {
                if (direction.x != 1) { new_direction = Vector2<int>(-1, 0); }
                break;
            }
            case SDLK_d : {
                if (direction.x != -1) { new_direction = Vector2<int>(1, 0); }
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
        move_type        = MOVE_TYPE_REVERSED;
        head_coordinates = snake_body.back();
    }
    else
    {
        move_type        = MOVE_TYPE_NORMAL;
        head_coordinates = snake_body.front();
    }
    direction = new_direction = prev_tail_coordinates - head_coordinates;
}

Vector2<int> Snake::GetHeadCoordinates()
{
    return head_coordinates;
}

void Snake::Render(SDL_Renderer* renderer)
{

    auto square_size = GameManager::GetInstance().GetSquareSize();
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
            if (i == snake_body.begin()) { SDL_RenderCopy(renderer, head_texture, nullptr, &texture_rect); }
            else { SDL_RenderCopy(renderer, body_texture, nullptr, &texture_rect); }
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
            if (i == snake_body.rbegin()) { SDL_RenderCopy(renderer, head_texture, nullptr, &texture_rect); }
            else { SDL_RenderCopy(renderer, body_texture, nullptr, &texture_rect); }
        }
    }
}
