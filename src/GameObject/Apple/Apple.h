#pragma once
#include "GameObject/GameObject.h"
#include "SDL2/SDL_image.h"
#include "Game_Manager/GM.h"
class Apple : public GameObject {
public:
    Apple(SDL_Window* window);
    ~Apple();
    void RandomApplePos();
    void ClearApplePos();
    void Render(SDL_Renderer* renderer) override;

protected:
    Vector2<Uint32> coordinates;
};