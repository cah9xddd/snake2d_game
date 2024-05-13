#pragma once
#include <iostream>

#include "GameObject/GameObject.h"

class Background : public GameObject {
public:
    Background(SDL_Renderer* renderer);
    ~Background() override;

    void Render(SDL_Renderer* renderer) override;
    void Update(std::chrono::milliseconds delta_time) override {};
    void HandleInput(SDL_Event& event) override {};

private:
    SDL_Texture* background_texture;
    SDL_Texture* game_name_texture;
};

inline Background::Background(SDL_Renderer* renderer)
{
    background_texture = IMG_LoadTexture(renderer, "assets/sprites/background.jpg");
    game_name_texture  = IMG_LoadTexture(renderer, "assets/sprites/name.png");
}

inline Background::~Background()
{
    std::cout << "BACKGROUND DESTRUCTOR" << std::endl;
    SDL_DestroyTexture(background_texture);
    background_texture = nullptr;
    SDL_DestroyTexture(game_name_texture);
    background_texture = nullptr;
}

inline void Background::Render(SDL_Renderer* renderer)
{
    SDL_Rect texture_rect;

    int w, h;
    SDL_GetWindowSize(SDL_RenderGetWindow(renderer), &w, &h);

    texture_rect.x = 0;
    texture_rect.y = 0;
    texture_rect.w = w;
    texture_rect.h = h;
    SDL_RenderCopy(renderer, background_texture, nullptr, &texture_rect);

    texture_rect.x = w * 0.25f;
    texture_rect.y = h * 0.1f;
    texture_rect.w = w * 0.5f;
    texture_rect.h = h * 0.2f;
    SDL_RenderCopy(renderer, game_name_texture, nullptr, &texture_rect);
}
