#pragma once
#include "GUI/GUI.h"
#include "SDL2/SDL.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_sdlrenderer.h"
class UIManager
{
public:
    UIManager();

    void PrepareUI();
    void RenderUI();
    void Close();

    void InitFontSize(SDL_Window *window);

private:
    void NewFrame();
};
