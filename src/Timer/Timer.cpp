#include "Timer.h"

SimpleTimer* SimpleTimer::timer = nullptr;

SimpleTimer* SimpleTimer::GetInstance() { return (timer != nullptr) ? timer : timer = new SimpleTimer; }

float SimpleTimer::GetDeltaTime() const { return delta_time; }

void SimpleTimer::Tick()
{
    delta_time = (SDL_GetTicks() - last_time) / 1000.f;

    last_time = SDL_GetTicks();
}
