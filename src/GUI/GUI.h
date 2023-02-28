#pragma once
#include <iostream>

#include "SDL2/SDL.h"
#include "imgui/imgui.h"

#include "GameManager/GameManager.h"

namespace GUI 
{
void ShowScoreWindow();
void ShowRestartWindow();
void ShowMainMenu();
}