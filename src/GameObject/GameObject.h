#pragma once
#include "SDL2/SDL.h"
#include "Vector2/Vector2.h"
class GameObject {
public:
    GameObject(SDL_Window* window);
    virtual ~GameObject();
    virtual void Render(SDL_Renderer* renderer);
    virtual void Update(double delta_time);
    virtual void UpdateWindowSize(SDL_Window* window);
    virtual void Init();
    virtual void HandleInput(SDL_Event& event);
    inline Vector2<int> GetCoordinates() { return coordinates; }

protected:
    Vector2<float> position;
    Vector2<int> window_size;
    Vector2<int> coordinates;

    SDL_Texture* texture;
};