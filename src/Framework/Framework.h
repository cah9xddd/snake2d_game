#pragma once
#include "GameObject/Field/Field.h"
#include "GameObject/Food/Food.h"
#include "GameObject/GameObject.h"
#include "GameObject/Snake/Snake.h"
#include "GameObject/Background/Background.h"
#include "Game_Manager/Game_Manager.h"
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
    static Framework* GetInstance() { return (framework != nullptr) ? framework : framework = new Framework; }

    bool Init(const char* title, int x, int y, int w, int h, bool fullscreen);
    void HandleEvents();
    void Update();
    void Render();
    void Close();
    
    void LoadMedia();

    inline bool Running() { return is_running; }
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    UI_Manager* ui_manager;
    Game_Manager* game_manager;

    Background* background;
    Field* field;
    Food* food;
    Snake* snake;

    bool is_running = false;

    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;

    static Framework* framework;
    Framework() {};
    Framework(Framework& other) = delete;
    void operator=(const Framework& other) = delete;
};