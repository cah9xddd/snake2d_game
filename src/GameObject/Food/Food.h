// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#pragma once

#include "GameObject/GameObject.h"

class Food : public GameObject {
public:
    enum FOOD_TYPE_ {
        FOOD_TYPE_NORMAL  = 10,
        FOOD_TYPE_REVERSE = 20,
    };

    Food(SDL_Renderer* renderer);
    ~Food() override;

    void Render(SDL_Renderer* renderer) override;
    void Update(std::chrono::milliseconds delta_time) override;
    void HandleInput(SDL_Event& event) override {};

    void CreateNewFood();

    FOOD_TYPE_ GetFoodType() const;

    Vector2<int> GetCoordinates();

private:
    FOOD_TYPE_ type;

    Vector2<int> coordinates;

    bool  shrinking = true;
    float scale     = 1.f;
    float border    = 0.f;

    SDL_Texture* food_texture;
    SDL_Texture* reverse_food_texture;
};