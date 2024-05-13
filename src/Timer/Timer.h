#pragma once
#include <chrono>

#include "SDL2/SDL.h"

class Timer {
public:
    explicit Timer() {};
    ~Timer() {};
    inline std::chrono::milliseconds GetDeltaTime() const;
    void                             Tick();

private:
    std::chrono::milliseconds delta_time = std::chrono::milliseconds(0);
    std::chrono::milliseconds last_time  = std::chrono::milliseconds(0);
};

inline std::chrono::milliseconds Timer::GetDeltaTime() const
{
    return delta_time;
}

inline void Timer::Tick()
{
    auto now = std::chrono::milliseconds(SDL_GetTicks());

    delta_time = (now - last_time);

    last_time = now;
}
