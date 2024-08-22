#include "room.hpp"
#include <SDL2/SDL_scancode.h>
#include <iostream>

Room::Room() :
    m_ctex(nullptr), m_ptex(nullptr), m_plyr(nullptr), m_gs(GameState::Game), m_failure(0), m_failureTimer(0), m_difficulty(0), m_selComp(0), m_fix(false)
{}

Room::Room(SDL_Texture& ctex, SDL_Texture& ptex, Uint32* ms, int* mx, int* my) :
    m_ctex(&ctex), m_ptex(&ptex), m_plyr(m_ptex), m_gs(GameState::Game), m_failure(0), m_failureTimer(0), m_difficulty(0), m_selComp(0), m_fix(false)
{
    for (int i = 0; i < COMP_NUM_X; i++)
    {
        for (int j = 0; j < COMP_NUM_Y; j++)
        {
            int x = ( ROOM_WIDTH - 64 - (2 * COMP_MARGIN)) / COMP_NUM_X * i;
            int y = (ROOM_HEIGHT - 64 - (2 * COMP_MARGIN)) / COMP_NUM_Y * i;

            m_comps.push_back(Computer(*m_ctex, x, y, m_ms, *m_mx, *m_my));
        }
    }
}

void Room::create(SDL_Texture& ctex, SDL_Texture& ptex, Uint32* ms, int* mx, int* my)
{
    m_failure = rand() % 25 + 5 ;
    m_ctex = &ctex;
    m_ptex = &ptex;
    m_plyr.setTexture(m_ptex);

    m_ms = ms;
    m_mx = &mx;
    m_my = &my;
    for (int i = 0; i < COMP_NUM_X; i++)
    {
        for (int j = 0; j < COMP_NUM_Y; j++)
        {
            int x = ( ROOM_WIDTH) / (COMP_NUM_X+1) * (i+1) - 32;
            int y = (ROOM_HEIGHT) / (COMP_NUM_Y+1) * (j+1) - 32;

            m_comps.push_back(Computer(*m_ctex, x, y, m_ms, *m_mx, *m_my));
        }
    }
}

Room::GameState Room::getState()
{
    return m_gs;
}

void Room::tick(float dt)
{
    if (!m_puzzleMode) m_plyr.tick(dt);
    for (int i = 0; i < m_comps.size(); i++)
    {
        m_comps[i].tick(dt);
        if (m_plyr.aabb(m_comps[i])) m_selComp = i;
        m_plyr.handleCol(m_comps[i]);
        if (m_comps[i].overworked()) m_gs = GameState::GameOver;
    }

    if (m_fix)
    {
        if (!m_puzzleMode && !m_comps[m_selComp].isOkay())
        {
            m_puzzleMode = true;
            m_comps[m_selComp].fix();
        }
    }
    m_fix = false;

    if (!m_puzzleMode) m_failureTimer += dt;
    if (m_failureTimer > m_failure)
    {
        m_failureTimer = 0;
        m_failure = rand() % 35 + 5 - m_difficulty;
        m_failure = SDL_clamp(m_failure, 10, INFINITY);
        m_difficulty += rand() % 20 == 19 ? 1 : 0;
        m_comps[rand() % m_comps.size()].forceFailure();
    }
}

void Room::draw(SDL_Renderer* ren) const
{
    for (int i = 0; i < m_comps.size(); i++)
        m_comps[i].draw(ren);
    m_plyr.draw(ren);
    for (int i = 0; i < m_comps.size(); i++)
        m_comps[i].drawPuzzle(ren);
}

void Room::getInput(const Uint8* keyboardstatus)
{
    if (!m_puzzleMode)
    {
        m_plyr.getInput(keyboardstatus);
        if (keyboardstatus[SDL_SCANCODE_SPACE]) m_fix = true;
    }
}
