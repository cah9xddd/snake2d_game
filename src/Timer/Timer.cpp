#include "Timer.h"

SimpleTimer* SimpleTimer::timer = nullptr;

void SimpleTimer::Tick()
{
    delta_time = (SDL_GetTicks() - last_time) / 1000.f;

    last_time = SDL_GetTicks();
}
