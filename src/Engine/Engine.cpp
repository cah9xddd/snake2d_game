#include "Engine.h"
#include "SDL.h"
#include <iostream>

Engine::Engine()
{
    std::cout << "HELLO FROM ENGINE" << std::endl;
}

Engine::~Engine()
{

}

bool Engine::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return 1;
    }
    SDL_Log("SDL initialized successfully.");
    return 0;
}
