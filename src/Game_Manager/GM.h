#pragma once
#include "SDL2/SDL.h"
#include "Vector2/Vector2.h"
#include <iostream>

class GM {
public:
    static GM* GetInstance() { return (GameManager != nullptr) ? GameManager : GameManager = new GM; };
    inline Vector2<float> GetSquareSize() { return square_size; };
    void PrintArray();
    inline int CheckSquare(Vector2<int> square) { return arr[square.x][square.y]; };
    inline void SetSquare(Vector2<int> square ,int value) { arr[square.x][square.y] = value; };
    void RefreshSquareSize(SDL_Window* window);

    bool YouLose(Vector2<int> coords);
    bool AppleEaten(Vector2<int> head_coordinates, Vector2<int> apple_coordinates);
    bool pause = false;
private :
    Vector2<float> square_size;

    static const int SIZE_X = 28;
    static const int SIZE_Y = 18;
    int arr[SIZE_X][SIZE_Y] = {0};

    static GM* GameManager;

    GM() {};
    GM(GM& other) = delete;
    void operator=(const GM& other) = delete;
};