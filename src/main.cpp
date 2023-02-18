#include "Engine/Engine.h"
#include <SDL.h>
Engine* engine = nullptr;
int main(int argc, char* argv[])
{
    engine = new Engine();
    if (!engine->Init("GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 450, SDL_WINDOW_SHOWN ))
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

    engine->Clean();
    engine->Close();
    return 0;
}
