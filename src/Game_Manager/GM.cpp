#include "GM.h"

GM* GM::GameManager = nullptr;

void GM::PrintArray()
{
    std::cout << std::endl;
    for (int y = 0; y < SIZE_Y; ++y)
    {
        for (int x = 0; x < SIZE_X; ++x)
        {
            std::cout << arr[x][y] << " ";
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
    if (coords.x < 0 || coords.y < 0 || coords.x > 27 || coords.y > 17) 
    {
        std::cout << "YOU LOSE" << std::endl;
        pause = true;
        return true;
    }
    else if (CheckSquare(coords) == 1)
    {
        std::cout << "YOU LOSE" << std::endl;
        pause = true;
        return true;
    }
    return false;
}

bool GM::AppleEaten(Vector2<int> head_coordinates, Vector2<int> apple_coordinates)
{
    return head_coordinates == apple_coordinates;
}
