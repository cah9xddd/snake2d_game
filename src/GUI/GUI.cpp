#include "GUI.h"

void TextCentered(std::string text, float margin)
{
    ImVec2 window_size = ImGui::GetWindowSize();

    auto textWidth = ImGui::CalcTextSize(text.c_str()).x;

    ImGui::SetCursorPosX((window_size.x - textWidth) * 0.5f);
    ImGui::SetCursorPosY((window_size.y - textWidth) * 0.5f + margin);

    ImGui::Text(text.c_str());
}
bool ButtonCentered(std::string text, float margin)
{
    ImVec2 window_size = ImGui::GetWindowSize();
    ImVec2 button_size;
    button_size.x = window_size.x / 5;
    button_size.y = window_size.y / 5;

    ImGui::SetCursorPosX(window_size.x * 0.5f - button_size.x / 2);
    ImGui::SetCursorPosY((window_size.y * 0.5f - button_size.y / 2) + margin);

    return ImGui::Button(text.c_str(), button_size);
}

void GUI::ShowScoreWindow()
{
    ImVec2 window_size = ImGui::GetMainViewport()->WorkSize;

    ImGui::SetNextWindowSize(ImVec2(window_size.x / 8.f, window_size.y));
    ImGui::SetNextWindowPos(ImVec2(window_size.x - window_size.x / 8.f, 0.f));
    ImGui::Begin("Score", nullptr,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize |
                     ImGuiWindowFlags_NoDecoration);

    TextCentered("SCORE", 0.f);
    TextCentered(std::to_string(GM::GetInstance()->score), ImGui::GetFontSize());

    ImGui::End();
}

void GUI::ShowRestartWindow()
{
    ImVec2 window_size = ImGui::GetMainViewport()->WorkSize;

    ImGui::SetNextWindowSize(ImVec2(window_size.x / 2, window_size.y / 2));
    ImGui::SetNextWindowPos(ImVec2(window_size.x / 4, window_size.y / 4));
    ImGui::Begin("Restart", nullptr,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize |
                     ImGuiWindowFlags_NoDecoration);

    ImVec2 window_size2 = ImGui::GetWindowSize();
    ImVec2 button_size;
    button_size.y = window_size2.y / 4;

    TextCentered("YOU LOSE", -button_size.y / 2);

    if (ButtonCentered("RESTART", 0.f)) { GM::GetInstance()->game_state = GAME_RESTART; };
    if (ButtonCentered("EXIT", button_size.y)) { GM::GetInstance()->game_state = GAME_EXIT; };

    ImGui::End();
}
