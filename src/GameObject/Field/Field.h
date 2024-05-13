// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#pragma once

#include "GameObject/GameObject.h"

class Field : public GameObject {
public:
    Field();
    ~Field() override;

    void Render(SDL_Renderer* renderer) override;
    void Update(std::chrono::milliseconds delta_time) override {};
    void HandleInput(SDL_Event& event) override {};

private:
    SDL_Rect field;
};