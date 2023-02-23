#pragma once
#include "GameObject/GameObject.h"
#include "Game_Manager/GM.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <list>
#include <string>
class Snake : public GameObject {
public:
    Snake(SDL_Window* window);
    ~Snake() {};

    void Render(SDL_Renderer* renderer) override;
    void Update(double delta_time) override;
    void HandleInput(SDL_Event& event) override;

    void Create();
    void IncrementBody(Vector2<int> coords);
    void ReverseSnake();

protected:
    std::list<Vector2<int>> snake_body;
    float passed_time = 0;
    Vector2<int> prev_tail_coords;

    // vunesti kak float
    float time_between_movements = 0.11f;

    Vector2<float> direction = {1.f, 0.f};
    Vector2<float> new_direction = {1.f, 0.f};
    SDL_Texture* texture;
};