#pragma once
#include "GameObject/GameObject.h"
#include "Game_Manager/GM.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <string>
class Snake : public GameObject {
public:
    Snake(SDL_Window* window);
    ~Snake() {};
    bool loadFromFile(SDL_Renderer* renderer, std::string path);
    void Render(SDL_Renderer* renderer) override;
    void Update(double delta_time) override;
    void HandleInput(SDL_Event& event) override;
    void UpdateWindowSize(SDL_Window* window) override;

protected:
    Vector2<int> head_pos;

    int speed = 150;
    Vector2<float> direction = {1.f, 0.f};
    Vector2<float> new_direction = {1.f, 0.f};
};