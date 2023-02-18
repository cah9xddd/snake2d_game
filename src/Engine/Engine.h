#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

class Engine {
public:
    Engine();
    ~Engine();

    bool Init(const char* title, int x, int y, int w, int h, Uint32 flags);
    void HandleEvents();
    void Update();
    void Render();
    void Clean();
    void Close();
    bool LoadMedia();
    inline bool Running() { return isRunning; }
    inline SDL_Renderer* GetRenderer() { return renderer; }

private:
    bool isRunning = false;
    SDL_Window* window;
    SDL_Renderer* renderer;
};