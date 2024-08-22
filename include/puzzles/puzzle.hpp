#pragma once
#include <SDL2/SDL_types.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include "../drawable.hpp"

class Puzzle : public arc::Drawable
{
protected:
    Uint32* m_mouseState;
    int* m_mx, * m_my;

public:
    Puzzle(Uint32* ms, int* mx, int* my);

public:
    virtual bool tick(SDL_KeyCode kc, float dt) {} // Return true if puzzle is solved
    virtual void draw(SDL_Renderer* ren) const {}
};
