#include "Framework.h"
#include "GUI/GUI.h"
#include <iostream>

Framework* Framework::framework = nullptr;

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
        std::cout << "SDL initialized successfully.\n";

        srand(SDL_GetTicks());

        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            std::cout << "Warning: Linear texture filtering not enabled!\n";
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
        window = SDL_CreateWindow(title, x, y, SCREEN_WIDTH, SCREEN_HEIGHT,
                                  fullscreen | SDL_WINDOW_RESIZABLE);
        if (window == nullptr)
        {
            SDL_LogCritical(1, "Failed to initialize window : %s\n", SDL_GetError());
            return false;
        }

        renderer =
            SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer == nullptr)
        {
            SDL_LogCritical(1, "Renderer could not be created! SDL Error: %s\n", SDL_GetError());
            return false;
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
        if (!(IMG_Init(imgFlags) & imgFlags))
        {
            SDL_LogCritical(1, "SDL_image could not initialize! SDL_image Error: %s\n",
                            IMG_GetError());
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
    else { std::cout << "Failed to initialize UI\n"; }

    return isRunning = true;
}

void Framework::HandleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT) { isRunning = false; }

        if (event.type == SDL_WINDOWEVENT)
        {
            GM::GetInstance()->RefreshSquareSize(window);
            if (field) { field->UpdateWindowSize(window); }
            if (apple) { apple->UpdateWindowSize(window); }
            if (snake) { snake->UpdateWindowSize(window); }
            SDL_RenderPresent(renderer);
        }

        const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.repeat == 0)
            {
                if (currentKeyStates[SDL_SCANCODE_ESCAPE]) { isRunning = false; }
            }
        }

        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (!game_manager->pause)
            {
                game_manager->PrintField();
                if (field != nullptr)
                {
                    delete field;
                    field = nullptr;
                }
                else { field = new Field(window); }
            }
        }

        if (!game_manager->pause) { snake->HandleInput(event); }
    }
}

void Framework::Update()
{
    double dt = SimpleTimer::GetInstance()->GetDeltaTime();
    if (!game_manager->pause)
    {
        if (game_manager->AppleEaten(snake->GetCoordinates(), apple->GetCoordinates()))
        {
            if (apple->GetType() == Food::FOOD_TYPE_REVERSE)
            {
                snake->ReverseSnake();
            }
            snake->IncrementBody(apple->GetCoordinates());
            apple->RandomApplePos();
        }
        else
        {
            if (snake) { snake->Update(dt); }
            if (apple) { apple->Update(dt); }
        }
    }
    else
    {
        if (game_manager->game_state == GAME_RESTART) { Restart(); }
        else if (game_manager->game_state == GAME_EXIT) { isRunning = false; }
    }
}

void Framework::Render()
{
    ui_manager->PrepareUI();

    SDL_RenderClear(renderer);

    if (field) { field->Render(renderer); }
    if (apple) { apple->Render(renderer); }
    if (snake) { snake->Render(renderer); }

    ui_manager->RenderUI();
    SDL_RenderPresent(renderer);
}

void Framework::Close()
{
    delete field;
    field = nullptr;
    delete apple;
    apple = nullptr;
    delete snake;
    snake = nullptr;
    delete game_manager;
    game_manager = nullptr;

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
    game_manager = GM::GetInstance();
    game_manager->RefreshSquareSize(window);

    field = new Field(window);

    snake = new Snake(window);

    apple = new Food(window);

    return true;
}

void Framework::Restart()
{
    game_manager->RestartGame();
    snake->Create();
    apple->RandomApplePos();

    game_manager->pause = false;

    game_manager->game_state = GAME_PLAYING;
}
