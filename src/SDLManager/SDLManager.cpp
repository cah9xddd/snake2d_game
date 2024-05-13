#include "SDLManager.h"

#include <iostream>

/// \param title the title of the window, in UTF-8 encoding
/// \param x the x position of the window, `SDL_WINDOWPOS_CENTERED`, or
///          `SDL_WINDOWPOS_UNDEFINED`
/// \param y the y position of the window, `SDL_WINDOWPOS_CENTERED`, or
///          `SDL_WINDOWPOS_UNDEFINED`
/// \param w the width of the window, in screen coordinates
/// \param h the height of the window, in screen coordinates
/// \param flags 0, or one or more SDL_WindowFlags OR'd together
/// \return is_running = true if all inits are ok , else false
SDLManager::SDLManager(const char* game_title, int x, int y, int w, int h, bool fullscreen)
{
    if (Init(game_title, x, y, w, h, fullscreen)) { sdl_is_initialized = true; }
}

SDLManager::~SDLManager()
{
    std::cout << "SDLMANAGER DESTRUCTOR" << std::endl;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window   = nullptr;
    renderer = nullptr;

    // Quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

SDL_Window* SDLManager::GetWindow()
{
    return window;
}

SDL_Renderer* SDLManager::GetRenderer()
{
    return renderer;
}

bool SDLManager::GetSDLIsInitialized()
{
    return sdl_is_initialized;
}

bool SDLManager::Init(const char* game_title = "Game",
                      int         x          = SDL_WINDOWPOS_CENTERED,
                      int         y          = SDL_WINDOWPOS_CENTERED,
                      int         w          = 1280,
                      int         h          = 720,
                      bool        fullscreen = true)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        // std::cout << "SDL initialized successfully.\n";

        srand(SDL_GetTicks());

        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            std::cout << "Warning: Linear texture filtering not enabled!\n";
        }
        Uint32 flags;
        if (fullscreen)
        {
            SDL_DisplayMode current;
            SDL_GetCurrentDisplayMode(0, &current);
            window_size.x = current.w;
            window_size.y = current.h;
            flags         = SDL_WINDOW_FULLSCREEN_DESKTOP;
        }
        else
        {
            window_size.x = w;
            window_size.y = h;
            flags         = SDL_WINDOW_RESIZABLE;
        }
        window = SDL_CreateWindow(game_title, x, y, window_size.x, window_size.y, flags);
        if (window == nullptr)
        {
            SDL_LogCritical(1, "Failed to initialize window : %s\n", SDL_GetError());
            return false;
        }
        SDL_SetWindowMinimumSize(window, 1280, 720);

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
    return true;
}
