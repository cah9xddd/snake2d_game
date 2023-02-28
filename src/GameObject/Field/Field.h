#pragma once
#include "GameObject/GameObject.h"
#include "Game_Manager/Game_Manager.h"
#include "SDL2/SDL.h"
#include "Vector2/Vector2.h"
class Field : public GameObject {
public:
    Field(SDL_Window* window);
    ~Field() override {};

    void Render(SDL_Renderer* renderer) override;
    void Update(float delta_time) override {};
    void HandleInput(SDL_Event& event) override {};
    void UpdateWindowSize(SDL_Window* window) override;

private:
    SDL_Rect field;
};