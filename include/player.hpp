#pragma once
#include "entity.hpp"
#include <string>
#include <SDL2/SDL_types.h>
#include <SDL2/SDL_render.h>

constexpr float PLAYER_VEL = 100;
// Player character
class Player : public arc::Entity
{
private:
    float m_vx, m_vy;
    float m_dt;
    SDL_Texture* m_tex;
    int m_anim; float m_animTimer;

public:
    Player();
    Player(SDL_Texture* m_tex);
    ~Player();

public:
    void getInput(const Uint8* keystate);
    void setTexture(SDL_Texture* tex);
    void handleCol(Entity other);

    void tick(float dt) override;
    void draw(SDL_Renderer* ren) const override;
};
