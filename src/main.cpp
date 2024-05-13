#include <iostream>

#include "SDL2/SDL.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

#include "Framework/Framework.h"

#if !SDL_VERSION_ATLEAST(2, 0, 17)
#  error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

int main(int argc, char* argv[])
{
    std::unique_ptr<Framework> framework(new Framework("SNAKE2D", 0, 0, 1920, 1080, true));

    while (framework->Running())
    {
        framework->HandleEvents();

        framework->Update();

        framework->Render();

        framework->TimerTick();
    }
    return 0;
}
