#include "GM.h"
GM* GM::GameManager = nullptr;

void GM::SetSquareSize(float x, float y)
{
    square_size.x = x;
    square_size.y = y;
}

void GM::PrintArray()
{
    for (int x = 0; x < SIZE_X; ++x)
    {
        for (int y = 0; y < SIZE_Y; ++y)
        {
            if(arr[x][y] == 2)
            {
                std::cout << "APPLE : " << x+1 << " x " << y+1 << std::endl;
            }
        }
    }
}
