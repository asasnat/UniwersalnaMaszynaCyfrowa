#include "puzzles/puzzle.hpp"

Puzzle::Puzzle(Uint32* ms, int* mx, int* my) :
    m_mouseState(ms), m_mx(mx), m_my(my)
{
}
