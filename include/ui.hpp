#pragma once
#include <SDL2/SDL_ttf.h>
#include <string>

namespace arc
{
    namespace ui
    {
        enum Font
        {
            Mono, Serif
        };

        bool init(std::string mono, std::string serif, SDL_Renderer* ren);
        void quit();

        void drawPoint(int x, int y, int size, SDL_Color col, bool centred = false);
        void drawLine(int x1, int y1, int x2, int y2, SDL_Color col);
        void drawText(int x, int y, std::string text, Font font, SDL_Color col, bool centred = true);
        void drawTextWrapped(int x, int y, std::string text, Font font, SDL_Color col, int wrap, bool centred = false);
        void drawFrame(int x, int y, int w, int h, SDL_Color col);
    }
}
