// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "GUI.h"
#include "string"

void GUI::ShowScoreWindow()
{
    ImVec2 viewport_size = ImGui::GetMainViewport()->WorkSize;

    ImGui::SetNextWindowSize(ImVec2(viewport_size.x / 8.f, viewport_size.y));
    ImGui::SetNextWindowPos(ImVec2(viewport_size.x - viewport_size.x / 8.f, 0.f));
    ImGui::Begin("Score", nullptr,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDecoration);

    ImVec2 window_size = ImGui::GetWindowSize();

    auto textWidth = ImGui::CalcTextSize("SCORE").x;
    ImGui::SetCursorPosX((window_size.x - textWidth) * 0.5f);
    ImGui::SetCursorPosY((window_size.y - textWidth) * 0.5f);
    ImGui::Text("SCORE");

    std::string str = std::to_string(GameManager::GetInstance().GetScore());
    textWidth       = ImGui::CalcTextSize(str.c_str()).x;
    ImGui::SetCursorPosX((window_size.x - textWidth) * 0.5f);
    ImGui::SetCursorPosY((window_size.y - textWidth) * 0.5f + ImGui::GetFontSize());
    ImGui::Text(str.c_str());

    ImGui::End();
}

void GUI::ShowRestartWindow()
{
    ImVec2 viewport_size = ImGui::GetMainViewport()->WorkSize;

    ImGui::SetNextWindowSize(ImVec2(viewport_size.x / 2.f, viewport_size.y / 2.f));
    ImGui::SetNextWindowPos(ImVec2(viewport_size.x / 4.f, viewport_size.y / 4.f));
    ImGui::Begin("Restart", nullptr,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDecoration);

    ImVec2 window_size = ImGui::GetWindowSize();
    ImVec2 button_size = { window_size.x / 2.f, window_size.y / 5.f };

    std::string str       = "SCORE : " + std::to_string(GameManager::GetInstance().GetScore());
    auto        textWidth = ImGui::CalcTextSize(str.c_str()).x;
    ImGui::SetCursorPosX((window_size.x - textWidth) * 0.5f);
    ImGui::SetCursorPosY((window_size.y - textWidth) * 0.5f - button_size.y * 0.3f);
    ImGui::Text(str.c_str());

    ImGui::SetCursorPosX(window_size.x * 0.5f - button_size.x / 2);
    ImGui::SetCursorPosY(window_size.y * 0.5f - button_size.y / 2);
    if (ImGui::Button("RESTART", button_size))
    {
        GameManager::GetInstance().SetGameState(GAME_STATE_NEW_GAME);
    }

    ImGui::SetCursorPosX(window_size.x * 0.5f - button_size.x / 2);
    ImGui::SetCursorPosY(window_size.y * 0.5f + button_size.y / 1.5f);
    if (ImGui::Button("EXIT", button_size)) { GameManager::GetInstance().SetGameState(GAME_STATE_EXIT); }

    ImGui::End();
}

void GUI::ShowMainMenu()
{
    ImVec2 viewport_size = ImGui::GetMainViewport()->WorkSize;

    ImGui::SetNextWindowSize(ImVec2(viewport_size.x, viewport_size.y));
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::Begin("MainMenu", nullptr,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDecoration);

    bool check_easy   = false;
    bool check_normal = false;
    bool check_hard   = false;
    switch (GameManager::GetInstance().GetDifficulty())
    {
        case DIFFICULTY_EASY :
            check_easy = true;
            break;
        case DIFFICULTY_NORMAL :
            check_normal = true;
            break;
        case DIFFICULTY_HARD :
            check_hard = true;
            break;
        default :
            break;
    }

    ImGui::SetCursorPosX(viewport_size.x * 0.30f);
    ImGui::SetCursorPosY(viewport_size.y * 0.45f);
    if (ImGui::Checkbox("EASY", &check_easy)) { GameManager::GetInstance().SetDifficulty(DIFFICULTY_EASY); }

    auto textWidth = ImGui::CalcTextSize("NORMAL").x;
    ImGui::SetCursorPosX(viewport_size.x * 0.5f - textWidth / 2.f);
    ImGui::SetCursorPosY(viewport_size.y * 0.45f);
    if (ImGui::Checkbox("NORMAL", &check_normal))
    {
        GameManager::GetInstance().SetDifficulty(DIFFICULTY_NORMAL);
    }

    ImGui::SetCursorPosX(viewport_size.x * 0.5f + textWidth);
    ImGui::SetCursorPosY(viewport_size.y * 0.45f);
    if (ImGui::Checkbox("HARD", &check_hard)) { GameManager::GetInstance().SetDifficulty(DIFFICULTY_HARD); }

    ImVec2 button_size;
    button_size.x = viewport_size.x / 4.f;
    button_size.y = viewport_size.y / 8.f;

    ImGui::SetCursorPosX(viewport_size.x * 0.5f - button_size.x / 2);
    ImGui::SetCursorPosY((viewport_size.y * 0.6f));
    if (ImGui::Button("PLAY", button_size)) { GameManager::GetInstance().SetGameState(GAME_STATE_NEW_GAME); }

    ImGui::SetCursorPosX(viewport_size.x * 0.5f - button_size.x / 2);
    ImGui::SetCursorPosY((viewport_size.y * 0.6f) + button_size.y * 1.5f);
    if (ImGui::Button("EXIT", button_size)) { GameManager::GetInstance().SetGameState(GAME_STATE_EXIT); }

    ImGui::End();
}
