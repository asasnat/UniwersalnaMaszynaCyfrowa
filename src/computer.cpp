#include "computer.hpp"
#include <iostream>

Computer::Computer() :
    arc::Entity(0, 0, 64, 64), m_tex(nullptr), m_okay(true), m_malfuncTimer(0), m_blinkTimer(0), m_blink(0), m_puzzle(nullptr)
{
}

Computer::Computer(SDL_Texture& tex, float x, float y, Uint32* ms, int* mx, int* my) :
    arc::Entity(x, y, 64, 64), m_tex(&tex), m_okay(true), m_malfuncTimer(0), m_blinkTimer(0), m_blink(0), m_puzzle(nullptr), m_ms(ms), m_mx(&mx), m_my(&my)
{
}

void Computer::forceFailure()
{
    m_okay = false;
    m_ft = (FailureType)0; // TODO: replace this with a rand() call once more than one puzzle is online
}

void Computer::fix()
{
    if (!m_puzzleOpen && !m_okay)
    {
        m_puzzleOpen = true;
        switch (m_ft)
        {
        case FailureType::Wires:
            m_puzzle = std::make_unique<WiresPuzzle>(m_ms, *m_mx, *m_my);
            break;

        default:
            break;
        }
    }
}

bool Computer::isOkay()
{
    return m_okay;
}

bool Computer::overworked()
{
    return m_malfuncTimer > GAMEOVER_THRESHOLD;
}

void Computer::tick(float dt)
{
    if (m_okay)
    {
        m_malfuncTimer = 0;
        m_blinkTimer = 0;
        m_blink = 0;
    }
    else
    {
        m_malfuncTimer += dt;
        m_blinkTimer += dt;
        if (m_blinkTimer >= .25f)
        {
            m_blinkTimer = 0;
            m_blink = !m_blink;
        }
    }

    if (m_puzzleOpen)
    {
        m_puzzle->tick(SDLK_1, dt);
    }
}

void Computer::draw(SDL_Renderer* ren) const
{
    SDL_SetRenderDrawColor(ren, m_blink ? 255 : 0, m_blink ? 0 : 255, 0, 255);
    SDL_FRect rect;
    rect.x = m_x;
    rect.y = m_y;
    rect.w = m_w;
    rect.h = m_h;
    SDL_Rect ref;
    ref.x = m_blink * 32;
    ref.y = 0;
    ref.w = 32;
    ref.h = 32;
    SDL_RenderFillRectF(ren, &rect);
}

void Computer::drawPuzzle(SDL_Renderer* ren) const
{
    if (m_puzzleOpen)
    {
        m_puzzle->draw(ren);
    }
}
