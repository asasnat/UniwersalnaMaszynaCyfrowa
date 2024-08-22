#pragma once
#include "computer.hpp"
#include "player.hpp"
#include "window.hpp"

#include <vector>
#include <SDL2/SDL_types.h>
#include <SDL2/SDL_render.h>

constexpr unsigned COMP_NUM_X  = 6;
constexpr unsigned COMP_NUM_Y  = 3;
constexpr unsigned ROOM_WIDTH  = 800;
constexpr unsigned ROOM_HEIGHT = 600;
constexpr unsigned COMP_MARGIN = 70;

// The room that the computers and player are placed in
class Room : public arc::Drawable
{
public:
    enum class GameState
    {
        Menu,
        Intro,
        Game,
        GameOver
    };

private:
    SDL_Texture* m_ctex; SDL_Texture* m_ptex;
    std::vector<Computer> m_comps;
    Player m_plyr;
    GameState m_gs;
    int m_selComp;
    bool m_fix;
    bool m_puzzleMode;

    float m_failure;
    float m_failureTimer;
    int m_difficulty;

    Uint32* m_ms;
    int** m_mx, ** m_my;

public:
    Room();
    Room(SDL_Texture& ctex, SDL_Texture& ptex, Uint32* ms, int* mx, int* my);
    void create(SDL_Texture& ctex, SDL_Texture& ptex, Uint32* ms, int* mx, int* my);

public:
    GameState getState();

public:
    void tick(float dt);
    void draw(SDL_Renderer* ren) const override;
    void getInput(const Uint8* keyboardstatus);
};
