#include "UIManager.h"

#include <iostream>

#include "GUI/GUI.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

/// @brief main init of our Dear ImGui
/// here we`re creating context  and set style for UI
/// set our font proportional to window size
/// @param window just our window
UIManager::UIManager(SDL_Window* window)
{
#ifdef SDL_HINT_IME_SHOW_UI
    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsClassic();
    ImGui::GetStyle().WindowBorderSize = 0.f;

    int width = 0, height = 0;
    SDL_GetWindowSize(window, &width, &height);

    ImFontConfig config;
    config.SizePixels = height / 15.f;
    auto asd = io.Fonts->AddFontFromFileTTF("assets/fonts/OpenSans-Regular.ttf", config.SizePixels, &config,
                                            io.Fonts->GetGlyphRangesDefault());
    IM_ASSERT(asd != nullptr);
}

UIManager::~UIManager()
{
    std::cout << "UIMANAGER DESTRUCTOR" << std::endl;
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

/// @brief must be called first at every frame and create new frame for UI
void UIManager::NewFrame()
{
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

/// @brief simpe func to prepare our UI for rendering , here we add our GUI functions
void UIManager::PrepareUI()
{
    NewFrame();

    switch (GameManager::GetInstance().GetGameState())
    {
        case GAME_STATE_MAIN_MENU : {
            GUI::ShowMainMenu();
            break;
        }
        case GAME_STATE_PLAYING : {
            GUI::ShowScoreWindow();
            break;
        }
        case GAME_STATE_LOSE : {
            GUI::ShowScoreWindow();
            GUI::ShowRestartWindow();
            break;
        }
        case GAME_STATE_WIN : {
            GUI::ShowScoreWindow();
            GUI::ShowRestartWindow();
            break;
        }
        default :
            break;
    }
    ImGui::Render();
}

/// @brief  must be called last at every frame and will render our UI
void UIManager::RenderUI()
{
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
}

/// @brief we must close our context at the end
void UIManager::Close()
{
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}