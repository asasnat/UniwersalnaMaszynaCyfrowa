#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "drawable.hpp"

constexpr unsigned SWIDTH  = 800;
constexpr unsigned SHEIGHT = 600;

namespace arc
{
    // Basic SDL2 render window
    class Window
    {
    private:
        SDL_Window* m_window; // not using smart ptrs for this because it's an SDL struct
        SDL_Renderer* m_ren;  // same with this

        unsigned m_w, m_h;
        std::string m_title;
        bool m_open;

    public:
        Window(std::string title, unsigned w, unsigned h);
        ~Window();

    public:
        bool isOpen() { return m_open; }
        SDL_Renderer* getSDLRenderer();

    public:
        void close();
        void pollEvents();
        SDL_Texture* loadTexture(std::string path);

        void clearScreen(SDL_Color col);
        void display();

        void draw(Drawable& drawable);
    };
}
