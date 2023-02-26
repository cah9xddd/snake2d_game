#pragma once
#include "SDL2/SDL.h"

class SimpleTimer {
public:
    static SimpleTimer* GetInstance() ;

    float GetDeltaTime() const;
    void Tick();

private:
    float delta_time = 0;
    float last_time = 0;

    static SimpleTimer* timer;
    SimpleTimer() {};
    SimpleTimer(SimpleTimer& other) = delete;
    void operator=(const SimpleTimer& other) = delete;
};