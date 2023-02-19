#include "Engine/Engine.h"
#include "SDL2/SDL.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_sdlrenderer.h"
#include <iostream>

#if !SDL_VERSION_ATLEAST(2, 0, 17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif
Engine* engine = nullptr;
int main(int argc, char* argv[])
{
    engine = new Engine();
     if (!engine->Init("GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, true))
    {
        SDL_LogCritical(1, "Failed initialize\n");
    }
    else
    {
        if (!engine->LoadMedia())
        {
            SDL_LogCritical(1, "Failed to load media!\n");
        }
    }

    while (engine->Running())
    {
        engine->HandleEvents();

        engine->Update();

        engine->Render();
    }

    engine->Close();
    return 0;
}
