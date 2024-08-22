#pragma once
#include "puzzle.hpp"
#include "../ui.hpp"

class WiresPuzzle : public Puzzle
{
private:
    enum PointColor
    {
        Red = 0, Green = 1, Blue = 2, Yellow = 3
    };
    struct StartPoint
    {
        PointColor color;
        bool connected;
        int connectedTo;
    };
    struct EndPoint
    {
        PointColor color;
    };

private:
    StartPoint m_sPoints[4];
    EndPoint m_ePoints[4];

public:
    WiresPuzzle(Uint32* ms, int* mx, int* my);

public:
    bool tick(SDL_KeyCode kc, float dt) override;
    void draw(SDL_Renderer* ren) const override;
};
