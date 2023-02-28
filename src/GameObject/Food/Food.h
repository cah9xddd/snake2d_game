#pragma once
#include "GameObject/GameObject.h"
#include "Game_Manager/Game_Manager.h"
#include "SDL2/SDL_image.h"
class Food : public GameObject {
public:
    enum FOOD_TYPE_ {
        FOOD_TYPE_NORMAL = 10,
        FOOD_TYPE_REVERSE = 20,
    };

    Food(SDL_Window* window);
    ~Food() override;

    void Render(SDL_Renderer* renderer) override;
    void Update(float delta_time) override;
    void HandleInput(SDL_Event& event) override {};

    void CreateNewFood();

    FOOD_TYPE_ GetFoodType() const;

private:
    FOOD_TYPE_ type;

    bool shrinking = true;

    float scale = 1.f;
    float border = 0.f;

    SDL_Texture* food_t;
    SDL_Texture* reverse_food_t;
};