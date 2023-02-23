#pragma once
#include "GameObject/GameObject.h"
#include "Game_Manager/GM.h"
#include "SDL2/SDL_image.h"
class Food : public GameObject {
public:
    enum FOOD_TYPE_ {
        FOOD_TYPE_NORMAL = 0,
        FOOD_TYPE_REVERSE = 1,
    };

    Food(SDL_Window* window);
    ~Food();
    
    void Render(SDL_Renderer* renderer) override;
    void Update(double delta_time) override;
    void HandleInput(SDL_Event& event) override {};
    void UpdateWindowSize(SDL_Window* window) override;

    void RandomApplePos();

    inline FOOD_TYPE_ GetType() { return type;}

private:
    FOOD_TYPE_  type;

    float scale = 1.f;
    float border = 0.f;

    SDL_Texture* texture1;
    SDL_Texture* texture2;


    
};