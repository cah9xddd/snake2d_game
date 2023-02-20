#pragma once
#include "../GameObject.h"
#include "SDL2/SDL.h"
#include "Vector2/Vector2.h"
class Field : public GameObject
{
public:
    Field(SDL_Window* window);
    ~Field() {};
    void Render(SDL_Renderer* renderer) override;
    inline Vector2<float> GetSquareSize() { return square_size;};
private:
    Vector2<float> square_size;
    SDL_Rect field;
    
};