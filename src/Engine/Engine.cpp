#include "Engine.h"
#include <iostream>

Engine::Engine()
{
    std::cout << "HELLO FROM ENGINE" << std::endl;
}

Engine::~Engine() {};


/// \param title the title of the window, in UTF-8 encoding
/// \param x the x position of the window, `SDL_WINDOWPOS_CENTERED`, or
///          `SDL_WINDOWPOS_UNDEFINED`
/// \param y the y position of the window, `SDL_WINDOWPOS_CENTERED`, or
///          `SDL_WINDOWPOS_UNDEFINED`
/// \param w the width of the window, in screen coordinates
/// \param h the height of the window, in screen coordinates
/// \param flags 0, or one or more SDL_WindowFlags OR'd together
/// \return isRunning = true if all inits are ok , else false
bool Engine::Init(const char* title, int x, int y, int w, int h, Uint32 flags)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        SDL_LogCritical(1, "SDL initialized successfully.\n");

        srand(SDL_GetTicks());

        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            SDL_Log("Warning: Linear texture filtering not enabled!\n");
        }

        window = SDL_CreateWindow(title, x, y, w, h, flags);
        if (window == nullptr)
        {
            SDL_LogCritical(1, "Failed to initialize window : %s\n", SDL_GetError());
            return false;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer == nullptr)
        {
            SDL_LogCritical(1, "Renderer could not be created! SDL Error: %s\n", SDL_GetError());
            return false;
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
        if (!(IMG_Init(imgFlags) & imgFlags))
        {
            SDL_LogCritical(1, "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
            return false;
        }

        if (TTF_Init() == -1)
        {
            SDL_LogCritical(1, "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
            return false;
        }
    }
    else
    {
        SDL_LogCritical(1, "Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }

    return isRunning = true;
}

void Engine::HandleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        std::cout << "CLOSING WINDOW\n";
        break;
    default:
        break;
    }
}

void Engine::Update()
{
    // std::cout << "123" << std::endl;
}

void Engine::Render()
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);


    SDL_RenderPresent(renderer);
}

void Engine::Close()
{
    // Destroy window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = nullptr;
    renderer = nullptr;

    // Quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    std::cout << "GAME CLEARED" << std::endl;
}

bool Engine::LoadMedia()
{
    return true;
}
