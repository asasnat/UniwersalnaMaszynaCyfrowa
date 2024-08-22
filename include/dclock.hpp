#pragma once
#include <SDL2/SDL_timer.h>

namespace arc
{
    // Basic clock used for measuring deltaTime
    struct DeltaClock
    {
        Uint64 now = SDL_GetPerformanceCounter();
        Uint64 last = 0;
        float dt;

        void Tick()
        {
            last = now;
            now = SDL_GetPerformanceCounter();
            dt = ((now - last) / (float)SDL_GetPerformanceFrequency());
        }
    };
}
