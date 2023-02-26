#include "Framework/Framework.h"
#include "SDL2/SDL.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_sdlrenderer.h"
#include <iostream>
#include "Timer/Timer.h"

#if !SDL_VERSION_ATLEAST(2, 0, 17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

int main(int argc, char* argv[])
{
    Framework* framework = Framework::GetInstance();
    if (!framework->Init("GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, false))
    {
        std::cout << "Failed initialize framework\n";
    }
    else
    {
        framework->LoadMedia();
    }

    while (framework->Running())
    {
        framework->HandleEvents();

        framework->Update();

        framework->Render();

        SimpleTimer::GetInstance()->Tick();
    }
    
    framework->Close();
    return 0;
}
