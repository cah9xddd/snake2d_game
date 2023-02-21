#pragma once
#include "SDL2/SDL_image.h"
#include "GameObject/GameObject.h"
#include <string>
#include <iostream>
#include "Game_Manager/GM.h"
class Snake : public GameObject
{
public:
    Snake(SDL_Window* window);
    ~Snake();
    bool loadFromFile(SDL_Renderer* renderer , std::string path);
    void Render(SDL_Renderer* renderer) override;
    void Update() override;

protected:

};