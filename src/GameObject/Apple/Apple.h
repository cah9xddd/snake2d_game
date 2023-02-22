#pragma once
#include "GameObject/GameObject.h"
#include "Game_Manager/GM.h"
#include "SDL2/SDL_image.h"
class Apple : public GameObject {
public:
    Apple(SDL_Window* window);
    ~Apple();
    void RandomApplePos();
    void ClearApplePos();
    void Render(SDL_Renderer* renderer) override;
    void UpdateWindowSize(SDL_Window* window) override;
};