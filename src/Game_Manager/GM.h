#pragma once
#include "SDL2/SDL.h"
#include "Vector2/Vector2.h"
#include <iostream>
class GM {
public:
    static GM* GetInstance() { return (GameManager != nullptr) ? GameManager : GameManager = new GM; };
    ~GM() {};
    inline Vector2<float> GetSquareSize() { return square_size; };
    void PrintArray();
    inline Uint32 CheckSquare(Uint32 x, Uint32 y) { return arr[x][y]; };
    inline void SetSquare(Uint32 x, Uint32 y, Uint32 value) { arr[x][y] = value; };
    void RefreshSquareSize(SDL_Window* window);
private:
    static GM* GameManager;

    Vector2<float> square_size;

    static const Uint32 SIZE_X = 28;
    static const Uint32 SIZE_Y = 18;
    Uint32 arr[SIZE_X][SIZE_Y] = {0};

    GM() {};
    GM(GM& other) = delete;
    void operator=(const GM& other) = delete;
};