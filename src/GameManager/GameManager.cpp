// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "GameManager.h"

GameManager* GameManager::game_manager = nullptr;

GameManager& GameManager::GetInstance()
{
    if (game_manager == nullptr)
    {
        game_manager = new GameManager;
        return *game_manager;
    }
    return *game_manager;
}

Vector2<float> GameManager::GetSquareSize() const
{
    return square_size;
}

void GameManager::SetSquare(Vector2<int> square, int value)
{
    field[square.x][square.y] = value;
}

/// @param square square coords to check
/// @return return square value
int GameManager::CheckSquare(Vector2<int> square) const
{
    return field[square.x][square.y];
}

/// @brief refresh square size every time when window size changed
void GameManager::RefreshSquareSize(SDL_Window* window)
{
    int size_x = 0;
    int size_y = 0;
    SDL_GetWindowSize(window, &size_x, &size_y);

    GameManager::GetInstance().square_size.x = (size_x - (size_x / 8.f)) / (float)SIZE_X;
    GameManager::GetInstance().square_size.y = size_y / (float)SIZE_Y;
}

bool GameManager::CheckLose(Vector2<int> coords)
{
    if (coords.x < 0 || coords.y < 0 || coords.x == SIZE_X || coords.y == SIZE_Y)
    {
        game_state = GAME_STATE_LOSE;
        return true;
    }
    else if (CheckSquare(coords) == 1)
    {
        game_state = GAME_STATE_LOSE;
        return true;
    }
    return false;
}

bool GameManager::IsFoodEaten(Vector2<int> head_coordinates, Vector2<int> food_coordinates)
{
    return head_coordinates == food_coordinates;
}

void GameManager::RestartGame()
{
    for (int y = 0; y < SIZE_Y; ++y)
    {
        for (int x = 0; x < SIZE_X; ++x) { field[x][y] = 0; }
    }
    score = 0;
}

void GameManager::SetDifficulty(DIFFICULTY_ new_difficulty)
{
    difficulty = new_difficulty;
}

DIFFICULTY_ GameManager::GetDifficulty() const
{
    return difficulty;
}

void GameManager::SetGameState(GAME_STATE_ new_game_state)
{
    game_state = new_game_state;
}

GAME_STATE_ GameManager::GetGameState() const
{
    return game_state;
}

int GameManager::GetScore() const
{
    return score;
}

void GameManager::AddToScore(int num)
{
    score += num;
}

int GameManager::GetFoodLeft() const
{
    return food_left;
}

void GameManager::DecreaseFoodLeft()
{
    --food_left;
}

GameManager::~GameManager()
{
    std::cout << "GameManager DESTRUCTOR" << std::endl;
    delete game_manager;
    game_manager = nullptr;
}
