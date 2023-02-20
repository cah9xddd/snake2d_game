#pragma once
#include "SDL2/SDL_image.h"
#include "GameObject/GameObject.h"
class Snake : public GameObject
{
public:
    Snake(SDL_Window* window);
    ~Snake();

    void Render(SDL_Renderer* renderer) override;
protected:

};