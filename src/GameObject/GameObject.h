#pragma once
#include <vector>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "Vector2/Vector2.h"

class GameObject {
public:
    explicit GameObject() {};
    virtual ~GameObject() {};

    virtual void Render(SDL_Renderer* renderer) {};
    virtual void Update(float delta_time) {};
    virtual void HandleInput(SDL_Event& event) {};
};