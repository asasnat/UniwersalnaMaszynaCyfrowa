#pragma once
#include "entity.hpp"
#include "puzzles/puzzles.hpp"
#include <memory>

constexpr float GAMEOVER_THRESHOLD = 60; // how high Computer::m_malfuncTimer may go before a game over is declared

// One of several 60's-era computers that Mr. Word has to maintain
class Computer : public arc::Entity
{
private:
    enum class FailureType
    {
        Wires = 0
    };

private:
    SDL_Texture* m_tex;
    bool m_okay; // whether the computer is RUNning or needs maintenance
    float m_malfuncTimer; // how long the computer has been offline
    float m_blinkTimer;
    int m_blink;

    FailureType m_ft;
    bool m_puzzleOpen;
    std::unique_ptr<Puzzle> m_puzzle;

    Uint32* m_ms;
    int** m_mx, ** m_my;

public:
    Computer();
    Computer(SDL_Texture& tex, float x, float y, Uint32* ms, int* mx, int* my);

public:
    void forceFailure();
    void fix();
    bool isOkay();
    bool overworked();

public:
    void tick(float dt) override;
    void draw(SDL_Renderer* ren) const override;
    void drawPuzzle(SDL_Renderer* ren) const;
};
