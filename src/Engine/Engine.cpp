#include "Engine.h"
#include "GUI/GUI.h"
#include <iostream>
/// \param title the title of the window, in UTF-8 encoding
/// \param x the x position of the window, `SDL_WINDOWPOS_CENTERED`, or
///          `SDL_WINDOWPOS_UNDEFINED`
/// \param y the y position of the window, `SDL_WINDOWPOS_CENTERED`, or
///          `SDL_WINDOWPOS_UNDEFINED`
/// \param w the width of the window, in screen coordinates
/// \param h the height of the window, in screen coordinates
/// \param flags 0, or one or more SDL_WindowFlags OR'd together
/// \return isRunning = true if all inits are ok , else false
bool Engine::Init(const char* title, int x, int y, int w, int h, bool fullscreen)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        SDL_LogCritical(1, "SDL initialized successfully.\n");

        srand(SDL_GetTicks());

        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            SDL_Log("Warning: Linear texture filtering not enabled!\n");
        }

        if (fullscreen)
        {
            SDL_DisplayMode current;
            SDL_GetCurrentDisplayMode(0, &current);
            SCREEN_WIDTH = current.w;
            SCREEN_HEIGHT = current.h;
        }
        else
        {
            SCREEN_WIDTH = w;
            SCREEN_HEIGHT = h;
        }
        window = SDL_CreateWindow(title, x, y, SCREEN_WIDTH, SCREEN_HEIGHT, fullscreen);
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

    ui_manager = new UI_Manager;

    if (ui_manager)
    {
        ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
        ImGui_ImplSDLRenderer_Init(renderer);
    }
    else
    {
        SDL_LogCritical(1, "Failed to initialize UI: ");
    }

    return isRunning = true;
}

void Engine::HandleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {

        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT)
            isRunning = false;
        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
            isRunning = false;
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        if (currentKeyStates[SDL_SCANCODE_ESCAPE])
        {
            isRunning = false;
        }
        else if (currentKeyStates[SDL_SCANCODE_SPACE])
        {
            ui_manager->ChangeUIColor();
        }
    }
}

void Engine::Update()
{
    // std::cout << "123" << std::endl;
}

void Engine::Render()
{


    ui_manager->PrepareUI();
    // ImGuiIO& io = ImGui::GetIO();
    // (void)io;
    // SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_RenderClear(renderer);

    ui_manager->RenderUI();

    SDL_RenderPresent(renderer);
}

void Engine::Close()
{

    ui_manager->Close();
    ui_manager = nullptr;

    // Destroy window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = nullptr;
    renderer = nullptr;

    // Quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

bool Engine::LoadMedia()
{
    return true;
}
