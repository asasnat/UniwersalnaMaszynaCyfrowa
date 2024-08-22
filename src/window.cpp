#include "window.hpp"
#include <iostream>
#include <SDL_image.h>

namespace arc
{
    Window::Window(std::string title, unsigned width, unsigned height)
        : m_title(title), m_w(width), m_h(height), m_open(false)
    {
        m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_w, m_h, 0);
        if (m_window == nullptr)
        {
            std::cerr << "Window initialisation failed: " << SDL_GetError() << std::endl;
            return;
        }

        m_ren = SDL_CreateRenderer(m_window, -1, 0);
        if (m_ren == nullptr)
        {
            std::cerr << "Renderer initialisation failed: " << SDL_GetError() << std::endl;
            return;
        }

        m_open = true;
    }

    Window::~Window()
    {
        if (m_window != nullptr) SDL_DestroyWindow(m_window);
        if (m_ren != nullptr) SDL_DestroyRenderer(m_ren);
    }

    SDL_Renderer* Window::getSDLRenderer()
    {
        return m_ren;
    }

    void Window::close()
    {
        m_open = false;
    }

    void Window::pollEvents()
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_QUIT:
                m_open = false;
                break;

            case SDL_KEYDOWN:
                switch (e.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    m_open = false;
                    break;

                default:
                    break;
                }
                break;

            default:
                break;
            }
        }
    }

    SDL_Texture* Window::loadTexture(std::string path)
    {
        SDL_Texture* tex = nullptr;
        tex = IMG_LoadTexture(m_ren, path.c_str());
        if (tex == nullptr)
            std::cerr << "Failed to load texture: " << SDL_GetError() << std::endl;
        return tex;
    }

    void Window::clearScreen(SDL_Color col)
    {
        SDL_SetRenderDrawColor(m_ren, col.r, col.g, col.b, col.a);
        SDL_RenderClear(m_ren);
    }

    void Window::display()
    {
        SDL_RenderPresent(m_ren);
    }

    void Window::draw(Drawable& drawable)
    {
        drawable.draw(m_ren);
    }
}
