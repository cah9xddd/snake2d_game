#pragma once
#include "SDL2/SDL.h"
#include "Vector2/Vector2.h"
#include <iostream>
enum GAME_STATE_
{
    GAME_STATE_MAIN_MENU = 0,
    GAME_STATE_PLAYING = 1,
    GAME_STATE_LOSE = 2,
    GAME_STATE_WIN = 3,
    GAME_STATE_NEW_GAME = 4,
    GAME_STATE_EXIT = 5,
};
enum DIFFICULTY_
{
    DIFFICULTY_EASY = 20,
    DIFFICULTY_NORMAL = 15,
    DIFFICULTY_HARD = 10,
};
class GameManager
{
public:
    static GameManager *GetInstance();

    static const int SIZE_X = 28;
    static const int SIZE_Y = 18;

    void SetSquare(Vector2<int> square, int value);
    Vector2<float> GetSquareSize() const;

    int CheckSquare(Vector2<int> square) const;

    void RefreshSquareSize(SDL_Window *window);

    bool CheckLose(Vector2<int> coords);

    bool IsFoodEaten(Vector2<int> head_coordinates, Vector2<int> apple_coordinates);

    void RestartGame();

    void SetDifficulty(DIFFICULTY_ new_difficulty);
    DIFFICULTY_ GetDifficulty() const;

    void SetGameState(GAME_STATE_ new_game_state);
    GAME_STATE_ GetGameState() const;

    int GetScore() const;
    void AddToScore(int num);

    int GetFoodLeft() const;
    void DecreaseFoodLeft();

private:
    DIFFICULTY_ difficulty = DIFFICULTY_NORMAL;
    GAME_STATE_ game_state = GAME_STATE_MAIN_MENU;

    int score = 0;
    int food_left = (SIZE_X * SIZE_Y) - 3;

    Vector2<float> square_size;

    int field[SIZE_X][SIZE_Y] = {0};

    static GameManager * game_manager;
    GameManager(){};
    GameManager(GameManager &other) = delete;
    void operator=(const GameManager &other) = delete;
};