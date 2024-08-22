#include "player.hpp"
#include <SDL2/SDL_keycode.h>
#include <iostream>

Player::Player() :
    arc::Entity(50, 50, 32, 52), m_vx(0), m_vy(0), m_tex(nullptr), m_anim(0), m_dt(0)
{}

Player::Player(SDL_Texture* tex) :
    arc::Entity(50, 50, 32, 52), m_vx(0), m_vy(0), m_tex(tex), m_anim(0), m_dt(0)
{}

Player::~Player()
{
    SDL_DestroyTexture(m_tex);
}

void Player::getInput(const Uint8* keystate)
{
    m_vx = -keystate[SDL_SCANCODE_LEFT] * PLAYER_VEL + keystate[SDL_SCANCODE_RIGHT] * PLAYER_VEL;
    m_vy = -keystate[SDL_SCANCODE_UP]   * PLAYER_VEL + keystate[SDL_SCANCODE_DOWN]  * PLAYER_VEL;
}

void Player::setTexture(SDL_Texture* tex)
{
    m_tex = tex;
}

void Player::handleCol(Entity other)
{
    if (aabb(other))
    {
        m_x -= m_vx * m_dt;
        m_y -= m_vy * m_dt;
    }
}

void Player::tick(float dt)
{
    m_dt = dt;
    m_x += m_vx * dt;
    m_y += m_vy * dt;
    if (fabs(m_vx) > 0 || fabs(m_vy) > 0) m_animTimer += dt;
    else { m_animTimer = 0; m_anim = 0; }
    if (m_animTimer >= .2f)
    {
        m_animTimer = 0;
        m_anim = !m_anim; // nobody's gonna know
        // they're gonna know
        // how are they gonna know?
        // the code's open source you dumbarse
        // oh :(
    }
}

void Player::draw(SDL_Renderer* ren) const
{
    SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
    SDL_FRect rect;
    rect.x = m_x;
    rect.y = m_y;
    rect.w = m_w;
    rect.h = m_h;
    SDL_Rect ref;
    ref.x = m_anim * 32;
    ref.y = 0;
    ref.w = 32;
    ref.h = 32;
    SDL_RenderFillRectF(ren, &rect);
}
