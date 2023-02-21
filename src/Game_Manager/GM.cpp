#include "GM.h"

GM* GM::GameManager = nullptr;

void GM::PrintArray()
{
    for (int x = 0; x < SIZE_X; ++x)
    {
        for (int y = 0; y < SIZE_Y; ++y)
        {
            if (arr[x][y] == 2)
            {
                std::cout << "APPLE : " << x + 1 << " x " << y + 1 << std::endl;
            }
        }
    }
}

void GM::RefreshSquareSize(SDL_Window* window)
{
    int size_x = 0;
    int size_y = 0;
    SDL_GetWindowSize(window, &size_x, &size_y);

    GM::GetInstance()->square_size.x = ((size_x - size_x / 8.f) / 28.f);
    GM::GetInstance()->square_size.y = (size_y / 18.f);
}
