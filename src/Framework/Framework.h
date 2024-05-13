// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#pragma once
#include <memory>
#include <vector>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include "GameManager/GameManager.h"
#include "GameObject/Background/Background.h"
#include "GameObject/Field/Field.h"
#include "GameObject/Food/Food.h"
#include "GameObject/GameObject.h"
#include "GameObject/Snake/Snake.h"
#include "SDLManager/SDLManager.h"
#include "Timer/Timer.h"
#include "UIManager/UIManager.h"

class Framework {
public:
    explicit Framework(const char* game_title, int x, int y, int w, int h, bool fullscreen);
    ~Framework();
    // bool Init(const char *game_title, int x, int y, int w, int h, bool fullscreen);
    void HandleEvents();
    void Update();
    void Render();
    void LoadMedia();
    void TimerTick();

    inline bool Running() { return is_running; }

private:
    bool is_running = false;

    int screen_width;
    int screen_height;

    std::unique_ptr<SDLManager> sdl_manager;
    std::unique_ptr<UIManager>  ui_manager;
    std::unique_ptr<Timer>      timer;

    std::unique_ptr<Background> background;
    std::unique_ptr<Field>      field;
    std::unique_ptr<Snake>      snake;
    std::unique_ptr<Food>       food;
};