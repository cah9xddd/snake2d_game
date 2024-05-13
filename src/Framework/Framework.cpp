// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Framework.h"

#include <iostream>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

/// \param title the title of the window, in UTF-8 encoding
/// \param x the x position of the window, `SDL_WINDOWPOS_CENTERED`, or
///          `SDL_WINDOWPOS_UNDEFINED`
/// \param y the y position of the window, `SDL_WINDOWPOS_CENTERED`, or
///          `SDL_WINDOWPOS_UNDEFINED`
/// \param w the width of the window, in screen coordinates
/// \param h the height of the window, in screen coordinates
/// \param flags 0, or one or more SDL_WindowFlags OR'd together
/// \return is_running = true if all inits are ok , else false
Framework::Framework(const char* game_title, int x, int y, int w, int h, bool fullscreen)
{
    sdl_manager = std::make_unique<SDLManager>(game_title, x, y, w, h, fullscreen);
    if (sdl_manager->GetSDLIsInitialized() == true)
    {
        ui_manager = std::make_unique<UIManager>(sdl_manager->GetWindow());
        if (ui_manager)
        {
            ImGui_ImplSDL2_InitForSDLRenderer(sdl_manager->GetWindow(), sdl_manager->GetRenderer());
            ImGui_ImplSDLRenderer2_Init(sdl_manager->GetRenderer());

            LoadMedia();
            is_running = true;
        }
        else { std::cout << "Failed to initialize UI and Load Media\n"; }
    }
}

void Framework::LoadMedia()
{
    GameManager::GetInstance().RefreshSquareSize(sdl_manager->GetWindow());

    timer      = std::make_unique<Timer>();
    field      = std::make_unique<Field>();
    snake      = std::make_unique<Snake>(sdl_manager->GetRenderer());
    food       = std::make_unique<Food>(sdl_manager->GetRenderer());
    background = std::make_unique<Background>(sdl_manager->GetRenderer());
}

Framework::~Framework()
{
    std::cout << "FRAMEWORK DESTRUCTOR" << std::endl;
}

void Framework::HandleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT) { is_running = false; }

        const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.repeat == 0)
            {
                if (currentKeyStates[SDL_SCANCODE_ESCAPE])
                {
                    if (GameManager::GetInstance().GetGameState() == GAME_STATE_MAIN_MENU)
                    {
                        is_running = false;
                    }
                    else { GameManager::GetInstance().SetGameState(GAME_STATE_MAIN_MENU); }
                }
                if (currentKeyStates[SDL_SCANCODE_F1])
                {
                    if (GameManager::GetInstance().GetGameState() != GAME_STATE_MAIN_MENU)
                    {
                        GameManager::GetInstance().SetGameState(GAME_STATE_NEW_GAME);
                    }
                }
            }
        }
        if (GameManager::GetInstance().GetGameState() == GAME_STATE_PLAYING) { snake->HandleInput(event); }
    }
}

void Framework::Update()
{
    auto dt = timer->GetDeltaTime();
    switch (GameManager::GetInstance().GetGameState())
    {
        case (GAME_STATE_PLAYING) : {
            if (GameManager::GetInstance().IsFoodEaten(snake->GetHeadCoordinates(), food->GetCoordinates()))
            {
                GameManager::GetInstance().DecreaseFoodLeft();
                if (GameManager::GetInstance().GetFoodLeft() == 0)
                {
                    GameManager::GetInstance().SetGameState(GAME_STATE_WIN);
                    return;
                }
                if (food->GetFoodType() == Food::FOOD_TYPE_REVERSE) { snake->ReverseSnake(); }
                GameManager::GetInstance().AddToScore(food->GetFoodType());
                snake->IncrementBody();
                food->CreateNewFood();
            }
            else
            {
                if (snake) { snake->Update(dt); }
                if (food) { food->Update(dt); }
            }

            break;
        }
        case (GAME_STATE_LOSE) :
            break;
        case (GAME_STATE_WIN) :
            break;
        case (GAME_STATE_NEW_GAME) : {
            GameManager::GetInstance().RestartGame();
            snake->Create(GameManager::GetInstance().GetDifficulty());
            food->CreateNewFood();
            GameManager::GetInstance().SetGameState(GAME_STATE_PLAYING);
            break;
        }
        case (GAME_STATE_EXIT) : {
            is_running = false;
            break;
        }
        default : {
            break;
        }
    }
}

void Framework::Render()
{
    ui_manager->PrepareUI();

    SDL_RenderClear(sdl_manager->GetRenderer());
    switch (GameManager::GetInstance().GetGameState())
    {
        case GAME_STATE_MAIN_MENU : {
            if (background) { background->Render(sdl_manager->GetRenderer()); }
            break;
        }
        case GAME_STATE_PLAYING : {
            if (field) { field->Render(sdl_manager->GetRenderer()); }
            if (food) { food->Render(sdl_manager->GetRenderer()); }
            if (snake) { snake->Render(sdl_manager->GetRenderer()); }
            break;
        }
        default : {
            if (field) { field->Render(sdl_manager->GetRenderer()); }
            if (food) { food->Render(sdl_manager->GetRenderer()); }
            if (snake) { snake->Render(sdl_manager->GetRenderer()); }
            break;
        }
    }

    ui_manager->RenderUI();
    SDL_RenderPresent(sdl_manager->GetRenderer());
}

void Framework::TimerTick()
{
    timer->Tick();
}
