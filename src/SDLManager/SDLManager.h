#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include "Vector2/Vector2.h"

class SDLManager {
public:
    SDLManager(const char* game_title, int x, int y, int w, int h, bool fullscreen);
    ~SDLManager();

    SDL_Window*   GetWindow();
    SDL_Renderer* GetRenderer();

    bool GetSDLIsInitialized();

private:
    bool Init(const char* game_title, int x, int y, int w, int h, bool fullscreen);

    bool sdl_is_initialized = false;

    Vector2<int> window_size;

    SDL_Renderer* renderer;
    SDL_Window*   window;
};