#pragma once
#include "SDL2/SDL.h"
#include "Vector2/Vector2.h"
class GameObject {
public:
    GameObject(SDL_Window* window);
    virtual ~GameObject();
    virtual void Render(SDL_Renderer* renderer);
    virtual void Update();
    virtual void UpdateWindowSize(SDL_Window* window);
    virtual void Init();

protected:
    Vector2<float> position;
    Vector2<int> window_size;
    SDL_Texture* texture;
};