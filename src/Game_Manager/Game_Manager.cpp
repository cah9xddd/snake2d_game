#include "Game_Manager.h"

Game_Manager* Game_Manager::GameManager = nullptr;

Game_Manager* Game_Manager::GetInstance()
{
    return (GameManager != nullptr) ? GameManager : GameManager = new Game_Manager;
}

void Game_Manager::SetSquare(Vector2<int> square, int value) { field[square.x][square.y] = value; }

Vector2<float> Game_Manager::GetSquareSize() const { return square_size; }

/// @param square square coords to check
/// @return return square value
int Game_Manager::CheckSquare(Vector2<int> square) const { return field[square.x][square.y]; }


/// @brief refresh square size every time when window size changed
void Game_Manager::RefreshSquareSize(SDL_Window* window)
{
    int size_x = 0;
    int size_y = 0;
    SDL_GetWindowSize(window, &size_x, &size_y);

    Game_Manager::GetInstance()->square_size.x = (size_x - (size_x / 8.f)) / (float)SIZE_X;
    Game_Manager::GetInstance()->square_size.y = size_y / (float)SIZE_Y;
}

bool Game_Manager::CheckLose(Vector2<int> coords)
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

bool Game_Manager::IsFoodEaten(Vector2<int> head_coordinates, Vector2<int> food_coordinates)
{
    return head_coordinates == food_coordinates;
}

void Game_Manager::RestartGame()
{
    for (int y = 0; y < SIZE_Y; ++y)
    {
        for (int x = 0; x < SIZE_X; ++x)
        {
            field[x][y] = 0;
        }
    }
    score = 0;
}

void Game_Manager::SetDifficulty(DIFFICULTY_ new_difficulty) { difficulty = new_difficulty; }

DIFFICULTY_ Game_Manager::GetDifficulty() const { return difficulty; }

void Game_Manager::SetGameState(GAME_STATE_ new_game_state) { game_state = new_game_state; }

GAME_STATE_ Game_Manager::GetGameState() const { return game_state; }

int Game_Manager::GetScore() const { return score; }

void Game_Manager::AddToScore(int num) { score += num; }

int Game_Manager::GetFoodLeft() const { return food_left; }

void Game_Manager::DecreaseFoodLeft() { --food_left; }
