#include "GameObject.h"

GameObject::GameObject(SDL_Window* window) { UpdateWindowSize(window); }

void GameObject::UpdateWindowSize(SDL_Window* window)
{
    SDL_GetWindowSize(window, &window_size.x, &window_size.y);
}

Vector2<int> GameObject::GetCoordinates() const  { return coordinates; }
