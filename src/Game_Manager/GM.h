#pragma once
#include "SDL2/SDL.h"
#include "Vector2/Vector2.h"
#include <iostream>

class GM {
public:
    static GM* GetInstance() { return (GameManager != nullptr) ? GameManager : GameManager = new GM; };
    inline Vector2<float> GetSquareSize() { return square_size; };
    void PrintArray();
    inline int CheckSquare(int x, int y) { return arr[x][y]; };
    inline void SetSquare(int x, int y, int value) { arr[x][y] = value; };
    void RefreshSquareSize(SDL_Window* window);
    void Update();
private:

    Vector2<float> square_size;

    static const int SIZE_X = 28;
    static const int SIZE_Y = 18;
    int arr[SIZE_X][SIZE_Y] = {0};

    static GM* GameManager;

    GM() {};
    GM(GM& other) = delete;
    void operator=(const GM& other) = delete;
};