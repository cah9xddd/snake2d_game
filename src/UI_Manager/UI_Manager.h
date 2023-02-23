#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_sdlrenderer.h"
#include "SDL2/SDL.h"
#include <string>
#include "GUI/GUI.h"
class UI_Manager 
{
public:
    UI_Manager();

    void PrepareUI();
    void RenderUI();
    void Close();

private:
    void NewFrame();
};
