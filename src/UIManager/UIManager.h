#pragma once
#include "SDL2/SDL.h"

class UIManager {
public:
    explicit UIManager(SDL_Window* window);
    ~UIManager();
    void PrepareUI();
    void RenderUI();
    void Close();

private:
    void NewFrame();
};
