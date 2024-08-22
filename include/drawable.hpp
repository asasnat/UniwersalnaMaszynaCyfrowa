#pragma once
#include <SDL2/SDL_render.h>

namespace arc
{
    // Anything that can be drawn by arc::Window
    class Drawable
    {
    public:
        virtual void draw(SDL_Renderer* ren) const {};
    };
}
