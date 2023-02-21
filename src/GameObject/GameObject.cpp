#include "GameObject.h"

GameObject::GameObject(SDL_Window* window)
{
    SDL_GetWindowSize(window, &window_size.x, &window_size.y);
    texture = nullptr;
}

GameObject::~GameObject()
{
    SDL_DestroyTexture(texture);
}

void GameObject::Render(SDL_Renderer* renderer)
{
}

void GameObject::Update()
{
    
}

void GameObject::UpdateWindowSize(SDL_Window* window)
{
    SDL_GetWindowSize(window, &window_size.x, &window_size.y);
}

void GameObject::Init()
{
}
