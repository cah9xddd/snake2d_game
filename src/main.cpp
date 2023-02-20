#include "Framework/Framework.h"
#include "SDL2/SDL.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_sdlrenderer.h"
#include <iostream>

#if !SDL_VERSION_ATLEAST(2, 0, 17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

Framework* framework = nullptr;
int main(int argc, char* argv[])
{
    framework = new Framework();
    if (!framework->Init("GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, false))
    {
        SDL_LogCritical(1, "Failed initialize\n");
    }
    else
    {
        if (!framework->LoadMedia())
        {
            SDL_LogCritical(1, "Failed to load media!\n");
        }
    }

    while (framework->Running())
    {
        framework->HandleEvents();

        framework->Update();

        framework->Render();
    }

    framework->Close();
    return 0;
}
