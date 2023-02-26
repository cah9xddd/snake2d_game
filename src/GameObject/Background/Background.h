#pragma once
#include "GameObject/GameObject.h"
#include "SDL2/SDL.h"
#include <iostream>
class Background : public GameObject {

public:
    Background(SDL_Window* window);
    ~Background();

    void Render(SDL_Renderer* renderer) override;
    void Update(double delta_time) override {};
    void HandleInput(SDL_Event& event) override {};

private:
    SDL_Texture* background_t;
    SDL_Texture* game_name_t;
};

inline Background::Background(SDL_Window* window) : GameObject(window)
{
    auto renderer = SDL_GetRenderer(window);
    background_t = IMG_LoadTexture(renderer, "assets/sprites/background.jpg");
    game_name_t = IMG_LoadTexture(renderer, "assets/sprites/name.png");
}

inline Background::~Background()
{
    SDL_DestroyTexture(background_t);
    background_t = nullptr;
    SDL_DestroyTexture(game_name_t);
    background_t = nullptr;
}

inline void Background::Render(SDL_Renderer* renderer)
{
    SDL_Rect texture_rect;

    texture_rect.x = 0;
    texture_rect.y = 0;
    texture_rect.w = window_size.x;
    texture_rect.h = window_size.y;
    SDL_RenderCopy(renderer, background_t, nullptr, &texture_rect);

    texture_rect.x = window_size.x * 0.25f;
    texture_rect.y = window_size.y * 0.1f;
    texture_rect.w = window_size.x * 0.5f;
    texture_rect.h = window_size.y * 0.2f;
    SDL_RenderCopy(renderer, game_name_t, nullptr, &texture_rect);
}
