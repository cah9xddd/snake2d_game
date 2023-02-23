#pragma once
#include "SDL2/SDL.h"
#include "Vector2/Vector2.h"
#include <iostream>
enum GAME_ {
    GAME_PLAYING = 0,
    GAME_LOSE = 1 << 1,
    GAME_WIN = 1 << 2,
    GAME_RESTART = 1 << 3,
    GAME_EXIT = 1 << 4,
};
class GM {
public:
    static GM* GetInstance()
    {
        return (GameManager != nullptr) ? GameManager : GameManager = new GM;
    };

    inline Vector2<float> GetSquareSize() { return square_size; };
    void PrintField();
    inline int CheckSquare(Vector2<int> square) { return field[square.x][square.y]; };
    inline void SetSquare(Vector2<int> square, int value) { field[square.x][square.y] = value; };
    void RefreshSquareSize(SDL_Window* window);

    bool YouLose(Vector2<int> coords);
    bool AppleEaten(Vector2<int> head_coordinates, Vector2<int> apple_coordinates);
    void RestartGame();
    void ClearField();
    bool pause = false;
    static const int SIZE_X = 28;
    static const int SIZE_Y = 18;
    GAME_ game_state = GAME_PLAYING;
    int score = 0;
private:
    Vector2<float> square_size;

    int field[SIZE_X][SIZE_Y] = {0};

    
    static GM* GameManager;

    GM() {};
    GM(GM& other) = delete;
    void operator=(const GM& other) = delete;
};