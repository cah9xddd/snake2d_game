#pragma once
#include "SDL2/SDL.h"

class Timer
{
public:
    explicit Timer(){};
    ~Timer();
    float GetDeltaTime() const;
    void Tick();

private:
    float delta_time = 0;
    float last_time = 0;

};