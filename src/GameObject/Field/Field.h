#pragma once
#include "../GameObject.h"
#include "SDL2/SDL.h"
#include "Vector2/Vector2.h"
#include "Game_Manager/GM.h"
class Field : public GameObject
{
public:
    Field(SDL_Window* window);
    ~Field() {};
    void Render(SDL_Renderer* renderer) override;
    void Update(double delta_time) override {};
    void HandleInput(SDL_Event& event) override {};
    void UpdateWindowSize(SDL_Window* window) override;
private:
    SDL_Rect field;
};