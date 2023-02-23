#include "UI_Manager.h"

UI_Manager::UI_Manager()
{
#ifdef SDL_HINT_IME_SHOW_UI
    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();
    ImGui::GetStyle().WindowBorderSize = 0.f;

    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    ImFontConfig config;
    config.SizePixels = 32;
    auto asd = io.Fonts->AddFontFromFileTTF("assets/fonts/OpenSans-Regular.ttf", 32.f, &config,
                                            io.Fonts->GetGlyphRangesDefault());
    IM_ASSERT(asd != nullptr);
}

void UI_Manager::Close()
{
    ImGui_ImplSDLRenderer_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void UI_Manager::NewFrame()
{
    ImGui_ImplSDLRenderer_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void UI_Manager::PrepareUI()
{
    NewFrame();

    GUI::ShowScoreWindow();

    if(GM::GetInstance()->game_state == GAME_LOSE)
    {
        GUI::ShowRestartWindow();
    }

    ImGui::Render();
}

void UI_Manager::RenderUI() { ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData()); }
