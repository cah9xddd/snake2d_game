#include <iostream>

#include "SDL2/SDL.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_sdlrenderer.h"

#include "Framework/Framework.h"

#if !SDL_VERSION_ATLEAST(2, 0, 17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

int main(int argc, char *argv[])
{
    std::unique_ptr<Framework> framework(new Framework("SNAKE2D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, true));

    while (framework->Running())
    {
        framework->HandleEvents();

        framework->Update();

        framework->Render();

        framework->TimerTick();
    }
    return 0;
}
