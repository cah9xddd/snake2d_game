#pragma once

#include "GameObject/GameObject.h"

class Field : public GameObject {
public:
    Field();
    ~Field() override;

    void Render(SDL_Renderer* renderer) override;
    void Update(std::chrono::milliseconds delta_time) override{};
    void HandleInput(SDL_Event& event) override {};

private:
    SDL_Rect field;
};