#include "UI_Manager.h"

UI_Manager::UI_Manager()
{
#ifdef SDL_HINT_IME_SHOW_UI
    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    SetUIColor(style_color);
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImFontConfig config;
    config.SizePixels = 32;
    auto asd = io.Fonts->AddFontFromFileTTF("assets/fonts/OpenSans-Regular.ttf", 32.0f, &config, io.Fonts->GetGlyphRangesDefault());
    IM_ASSERT(asd != nullptr);
}

UI_Manager::~UI_Manager()
{
}

void UI_Manager::SetUIColor(UI_Color_ color)
{
    switch (color)
    {
    case UI_Color_Classic:
        ImGui::StyleColorsClassic();
        style_color = UI_Color_Classic;
        break;
    case UI_Color_Dark:
        ImGui::StyleColorsDark();
        style_color = UI_Color_Dark;
        break;
    case UI_Color_Light:
        ImGui::StyleColorsLight();
        style_color = UI_Color_Light;
        break;
    default:
        break;
    }
}

void UI_Manager::ChangeUIColor()
{
    if (style_color == UI_Color_Light)
    {
        UI_Manager::SetUIColor(UI_Color_Classic);
    }
    else if (style_color == UI_Color_Classic)
    {
        UI_Manager::SetUIColor(UI_Color_Dark);
    }
    else if (style_color == UI_Color_Dark)
    {
        UI_Manager::SetUIColor(UI_Color_Light);
    }
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
