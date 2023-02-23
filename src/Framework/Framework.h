#pragma once
#include "GameObject/Field/Field.h"
#include "GameObject/Food/Food.h"
#include "GameObject/GameObject.h"
#include "GameObject/Snake/Snake.h"
#include "Game_Manager/GM.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"
#include "Timer/Timer.h"
#include "UI_Manager/UI_Manager.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_sdlrenderer.h"
#include <iostream>


class Framework {
public:
    static Framework* GetInstance()
    {
        return (framework != nullptr) ? framework : framework = new Framework;
    }

    bool Init(const char* title, int x, int y, int w, int h, bool fullscreen);
    void HandleEvents();
    void Update();
    void Render();
    void Close();
    bool LoadMedia();
    void Restart();
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
    GM* game_manager;

    Field* field;
    Food* apple;
    Snake* snake;

    bool isRunning = false;

    static Framework* framework;
    Framework() {};
    Framework(Framework& other) = delete;
    void operator=(const Framework& other) = delete;
};