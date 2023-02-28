#include "Timer.h"

#include <iostream>

Timer::~Timer()
{
    std::cout << "TIMER STRUCTOR" << std::endl;
}

float Timer::GetDeltaTime() const { return delta_time; }

void Timer::Tick()
{
    delta_time = (SDL_GetTicks() - last_time) / 1000.f;

    last_time = SDL_GetTicks();
}
