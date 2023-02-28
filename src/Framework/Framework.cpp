#include "Framework.h"
#include "GUI/GUI.h"
#include <iostream>

Framework *Framework::framework = nullptr;

/// \param title the title of the window, in UTF-8 encoding
/// \param x the x position of the window, `SDL_WINDOWPOS_CENTERED`, or
///          `SDL_WINDOWPOS_UNDEFINED`
/// \param y the y position of the window, `SDL_WINDOWPOS_CENTERED`, or
///          `SDL_WINDOWPOS_UNDEFINED`
/// \param w the width of the window, in screen coordinates
/// \param h the height of the window, in screen coordinates
/// \param flags 0, or one or more SDL_WindowFlags OR'd together
/// \return is_running = true if all inits are ok , else false
bool Framework::Init(const char *title, int x, int y, int w, int h, bool fullscreen)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        // std::cout << "SDL initialized successfully.\n";

        srand(SDL_GetTicks());

        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            std::cout << "Warning: Linear texture filtering not enabled!\n";
        }
        Uint32 flags;
        if (fullscreen)
        {
            SDL_DisplayMode current;
            SDL_GetCurrentDisplayMode(0, &current);
            screen_width = current.w;
            screen_height = current.h;
            flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
        }
        else
        {
            screen_width = w;
            screen_height = h;
            flags = SDL_WINDOW_RESIZABLE;
        }
        window = SDL_CreateWindow(title, x, y, screen_width, screen_height, flags);
        if (window == nullptr)
        {
            SDL_LogCritical(1, "Failed to initialize window : %s\n", SDL_GetError());
            return false;
        }
        SDL_SetWindowMinimumSize(window, 1280, 720);

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

    ui_manager = new UIManager;

    if (ui_manager)
    {
        ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
        ImGui_ImplSDLRenderer_Init(renderer);
        ui_manager->InitFontSize(window);
    }
    else
    {
        std::cout << "Failed to initialize UI\n";
    }

    return is_running = true;
}

void Framework::HandleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT)
        {
            is_running = false;
        }

        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED)
        {
            GameManager::GetInstance()->RefreshSquareSize(window);
            if (field)
            {
                field->UpdateWindowSize(window);
            }
            if (food)
            {
                food->UpdateWindowSize(window);
            }
            if (snake)
            {
                snake->UpdateWindowSize(window);
            }
            if (background)
            {
                background->UpdateWindowSize(window);
            }
            SDL_RenderPresent(renderer);
        }

        const Uint8 *currentKeyStates = SDL_GetKeyboardState(nullptr);
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.repeat == 0)
            {
                if (currentKeyStates[SDL_SCANCODE_ESCAPE])
                {
                    if (game_manager->GetGameState() == GAME_STATE_MAIN_MENU)
                    {
                        is_running = false;
                    }
                    else
                    {
                        game_manager->SetGameState(GAME_STATE_MAIN_MENU);
                    }
                }
                if (currentKeyStates[SDL_SCANCODE_F1])
                {

                    game_manager->SetGameState(GAME_STATE_NEW_GAME);
                }
            }
        }
        if (game_manager->GetGameState() == GAME_STATE_PLAYING)
        {
            snake->HandleInput(event);
        }
    }
}

void Framework::Update()
{
    float dt = SimpleTimer::GetInstance()->GetDeltaTime();
    switch (game_manager->GetGameState())
    {
    case (GAME_STATE_PLAYING):
    {
        if (game_manager->IsFoodEaten(snake->GetCoordinates(), food->GetCoordinates()))
        {
            game_manager->DecreaseFoodLeft();
            if (game_manager->GetFoodLeft() == 0)
            {
                game_manager->SetGameState(GAME_STATE_WIN);
                return;
            }
            if (food->GetFoodType() == Food::FOOD_TYPE_REVERSE)
            {
                snake->ReverseSnake();
            }
            game_manager->AddToScore(food->GetFoodType());
            snake->IncrementBody();
            food->CreateNewFood();
        }
        else
        {
            if (snake)
            {
                snake->Update(dt);
            }
            if (food)
            {
                food->Update(dt);
            }
        }

        break;
    }
    case (GAME_STATE_LOSE):
        break;
    case (GAME_STATE_WIN):
        break;
    case (GAME_STATE_NEW_GAME):
    {
        game_manager->RestartGame();
        snake->Create(game_manager->GetDifficulty());
        food->CreateNewFood();
        game_manager->SetGameState(GAME_STATE_PLAYING);
        break;
    }
    case (GAME_STATE_EXIT):
    {
        is_running = false;
        break;
    }
    default:
        break;
    }
}

void Framework::Render()
{
    ui_manager->PrepareUI();

    SDL_RenderClear(renderer);
    switch (game_manager->GetGameState())
    {
    case GAME_STATE_MAIN_MENU:
    {
        if (background)
        {
            background->Render(renderer);
        }
        break;
    }
    case GAME_STATE_PLAYING:
    {
        if (field)
        {
            field->Render(renderer);
        }
        if (food)
        {
            food->Render(renderer);
        }
        if (snake)
        {
            snake->Render(renderer);
        }
        break;
    }
    default:
    {
        if (field)
        {
            field->Render(renderer);
        }
        if (food)
        {
            food->Render(renderer);
        }
        if (snake)
        {
            snake->Render(renderer);
        }
        break;
    }
    }

    ui_manager->RenderUI();
    SDL_RenderPresent(renderer);
}

void Framework::Close()
{
    delete field;
    field = nullptr;
    delete food;
    food = nullptr;
    delete snake;
    snake = nullptr;
    delete background;
    background = nullptr;
    delete game_manager;
    game_manager = nullptr;

    // Close UI
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

void Framework::LoadMedia()
{
    game_manager = GameManager::GetInstance();
    game_manager->RefreshSquareSize(window);

    background = new Background(window);

    field = new Field(window);

    snake = new Snake(window);

    food = new Food(window);
}
