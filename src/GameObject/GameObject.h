#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Vector2/Vector2.h"
class GameObject {
public:
    GameObject(SDL_Window* window);
    virtual ~GameObject() {};

    virtual void Render(SDL_Renderer* renderer) = 0;
    virtual void Update(float delta_time) = 0;
    virtual void HandleInput(SDL_Event& event) = 0;

    virtual void UpdateWindowSize(SDL_Window* window);

    Vector2<int> GetCoordinates() const;

protected:
    Vector2<int> window_size;
    Vector2<int> coordinates;
};