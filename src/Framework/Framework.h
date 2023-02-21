#pragma once
#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"
#include "UI_Manager/UI_Manager.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_sdlrenderer.h"
#include "GameObject/GameObject.h"
#include "GameObject/Field/Field.h"
#include "GameObject/Snake/Snake.h"
#include "GameObject/Apple/Apple.h"
#include "Game_Manager/GM.h"
#include "Timer/Timer.h"


class Framework {
public:
    bool Init(const char* title, int x, int y, int w, int h, bool fullscreen);
    void HandleEvents();
    void Update();
    void Render();
    void Close();
    bool LoadMedia();

    inline bool Running() { return isRunning; }

    inline SDL_Renderer* GetRenderer() { return renderer; }
    inline SDL_Window* GetWindow() { return window; }
    inline UI_Manager* GetUI() { return ui_manager; }

    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    UI_Manager* ui_manager;

    GameObject* field;
    GameObject* apple;
    GameObject* snake;

    bool isRunning = false;
    bool isUpdating = true;
};