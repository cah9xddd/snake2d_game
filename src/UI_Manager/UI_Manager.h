#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_sdlrenderer.h"
#include "SDL2/SDL.h"
#include "string"
#include "GUI/GUI.h"
class UI_Manager 
{
public:
    enum UI_Color_ {
        UI_Color_Classic = 0,
        UI_Color_Dark = 1 << 0,
        UI_Color_Light = 1 << 1,
    };
    UI_Manager();
    ~UI_Manager();

    void SetUIColor(UI_Color_ color);
    void ChangeUIColor();
    void Close();
    void NewFrame();
private:
    UI_Color_ style_color = UI_Color_Light;
};
