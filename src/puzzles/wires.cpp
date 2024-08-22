#include "puzzles/wires.hpp"
#include <algorithm>

WiresPuzzle::WiresPuzzle(Uint32* ms, int* mx, int* my) :
    Puzzle(ms, mx, my)
{
    m_sPoints[0] = { Red, false, 0 };
    m_sPoints[1] = { Green, false, 0 };
    m_sPoints[2] = { Blue, false, 0 };
    m_sPoints[3] = { Yellow, false, 0 };

    m_ePoints[0] = { Red };
    m_ePoints[1] = { Green };
    m_ePoints[2] = { Blue };
    m_ePoints[3] = { Yellow };

    std::random_shuffle(std::begin(m_sPoints), std::end(m_sPoints));
    std::random_shuffle(std::begin(m_ePoints), std::end(m_ePoints));
}

bool WiresPuzzle::tick(SDL_KeyCode kc, float dt)
{
    
    return false;
}

void WiresPuzzle::draw(SDL_Renderer* ren) const
{
    arc::ui::drawLine(0, 0, *m_mx, *m_my, { 255,255,255,255 });
    arc::ui::drawFrame(0, 0, 400, 300, { 32, 32, 32, 255 });
    SDL_Color dc;
    for (int i = 0; i < 4; i++)
    {
        switch (m_sPoints[i].color)
        {
        case Red:
            dc = { 255, 0, 0, 255 };
            break;

        case Green:
            dc = { 0, 255, 0, 255 };
            break;

        case Blue:
            dc = { 0, 0, 255, 255 };
            break;

        case Yellow:
            dc = { 255, 255, 0, 255 };
            break;

        default:
            break;
        }
        arc::ui::drawPoint(-160, -110 + (75 * (i)), 20, dc, true);
    }
    for (int i = 0; i < 4; i++)
    {
        switch (m_ePoints[i].color)
        {
        case Red:
            dc = { 255, 0, 0, 255 };
            break;

        case Green:
            dc = { 0, 255, 0, 255 };
            break;

        case Blue:
            dc = { 0, 0, 255, 255 };
            break;

        case Yellow:
            dc = { 255, 255, 0, 255 };
            break;

        default:
            break;
        }
        arc::ui::drawPoint(160, -110 + (75 * (i)), 20, dc, true);
    }
}
