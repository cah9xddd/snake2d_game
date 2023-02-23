#include "GM.h"

GM* GM::GameManager = nullptr;

void GM::PrintField()
{
    std::cout << std::endl;
    for (int y = 0; y < SIZE_Y; ++y)
    {
        for (int x = 0; x < SIZE_X; ++x)
        {
            std::cout << field[x][y] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void GM::RefreshSquareSize(SDL_Window* window)
{
    int size_x = 0;
    int size_y = 0;
    SDL_GetWindowSize(window, &size_x, &size_y);

    GM::GetInstance()->square_size.x = (size_x - (size_x / 8.f)) / 28.f;
    GM::GetInstance()->square_size.y = size_y / 18.f;
}

bool GM::YouLose(Vector2<int> coords)
{
    if (coords.x < 0 || coords.y < 0 || coords.x == SIZE_X || coords.y == SIZE_Y)
    {
        std::cout << "YOU LOSE" << std::endl;
        pause = true;
        game_state = GAME_LOSE;
        return true;
    }
    else if (CheckSquare(coords) == 1)
    {
        std::cout << "YOU LOSE" << std::endl;
        pause = true;
        game_state = GAME_LOSE;
        return true;
    }
    return false;
}

bool GM::AppleEaten(Vector2<int> head_coordinates, Vector2<int> apple_coordinates)
{
    if (head_coordinates == apple_coordinates) { score += 10; }
    return head_coordinates == apple_coordinates;
}

void GM::RestartGame() 
{
    ClearField();
    score = 0; 
}

void GM::ClearField() 
{
    for (int y = 0; y < SIZE_Y; ++y)
    {
        for (int x = 0; x < SIZE_X; ++x)
        {
            field[x][y] = 0;
        }
    }
}
