// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#pragma once
#include <iostream>

#include "SDL2/SDL.h"
#include "imgui.h"

#include "GameManager/GameManager.h"

namespace GUI {
void ShowScoreWindow();
void ShowRestartWindow();
void ShowMainMenu();
}    // namespace GUI