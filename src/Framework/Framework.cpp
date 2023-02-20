#include "Framework.h"
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
bool Framework::Init(const char* title, int x, int y, int w, int h, bool fullscreen)
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
        window = SDL_CreateWindow(title, x, y, SCREEN_WIDTH, SCREEN_HEIGHT, fullscreen | SDL_WINDOW_RESIZABLE);
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

void Framework::HandleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {

        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT)
            isRunning = false;
        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
            isRunning = false;
        if (event.type == SDL_WINDOWEVENT)
        {
            switch (event.window.event)
            {
                case SDL_WINDOWEVENT_SIZE_CHANGED: {
                    SCREEN_WIDTH = event.window.data1;
                    SCREEN_HEIGHT = event.window.data2;
                    if (field != nullptr)
                    {
                        delete field;
                        field = nullptr;
                        field = new Field(window);
                    }
                    if(apple !=nullptr)
                    {
                        delete apple;
                        apple = nullptr;
                        apple = new Apple(window);
                    }
                    SDL_RenderPresent(renderer);
                    break;
                }
                case SDL_WINDOWEVENT_EXPOSED: {
                    SDL_RenderPresent(renderer);
                    break;
                }
            }
        }

        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        if (event.type == SDL_KEYDOWN)
        {   
            if (event.key.repeat == 0)
            {
                if (currentKeyStates[SDL_SCANCODE_ESCAPE])
                {
                    isRunning = false;
                }
                if (currentKeyStates[SDL_SCANCODE_SPACE])
                {
                    if (field != nullptr)
                    {
                        SDL_Log("DELETED FIELD");
                        delete field;
                        field = nullptr;
                    }
                    else
                    {
                        SDL_Log("CREATED FIELD");
                        field = new Field(window);
                    }

                    if (apple != nullptr)
                    {
                        SDL_Log("DELETED Apple");
                        delete apple;
                        apple = nullptr;
                    }
                    else
                    {
                        SDL_Log("CREATED Apple");
                        apple = new Apple(window);
                    }
                }
            }
        }

        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            GM::GetInstance()->PrintArray();
            if (field != nullptr)
            {
                SDL_Log("DELETED FIELD");
                delete field;
                field = nullptr;
            }
            else
            {
                SDL_Log("CREATED FIELD");
                field = new Field(window);
            }
        }
    }
}

void Framework::Update()
{
    // std::cout << "123" << std::endl;
}

void Framework::Render()
{
    if (isUpdating)
    {
        ui_manager->PrepareUI();

        SDL_RenderClear(renderer);

        
        if (field)
        {
            field->Render(renderer);
        }
        if (apple)
        {
            apple->Render(renderer);
        }

        ui_manager->RenderUI();
        SDL_RenderPresent(renderer);
    }
}

void Framework::Close()
{
    delete field;
    field = nullptr;
    delete apple;
    apple = nullptr;
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

bool Framework::LoadMedia()
{
    GM::GetInstance();
    field = new Field(window);

    GM::GetInstance()->SetSquareSize(field->GetSquareSize().x, field->GetSquareSize().y);

    apple = new Apple(window);
    

    return true;
}
