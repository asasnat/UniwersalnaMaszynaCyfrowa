#include "ui.hpp"
#include <iostream>
#include <memory>

namespace
{
    TTF_Font* monoFont, *serifFont;
    std::unique_ptr<SDL_Renderer*> renptr;
}

namespace arc
{
    namespace ui
    {
        // MANAGEMENT
        bool init(std::string mono, std::string serif, SDL_Renderer* ren)
        {
            monoFont = TTF_OpenFont(mono.c_str(), 22);
            if (monoFont == nullptr)
            {
                std::cerr << "Mono font initialisation failed: " << TTF_GetError() << std::endl;
                return false;
            }

            serifFont = TTF_OpenFont(serif.c_str(), 22);
            if (serifFont == nullptr)
            {
                std::cerr << "Serif font initalisation failed: " << TTF_GetError() << std::endl;
                return false;
            }

            renptr = std::make_unique<SDL_Renderer*>(ren);
            return true;
        }

        void quit()
        {
            TTF_CloseFont(monoFont);
            TTF_CloseFont(serifFont);
        }

        // DRAWING
        void drawPoint(int x, int y, int size, SDL_Color col, bool centred)
        {
            SDL_Rect rect;
            rect.w = size;
            rect.h = size;

            if (centred)
            {
                SDL_Rect vp;
                SDL_RenderGetViewport(*renptr, &vp);
                rect.x = vp.w / 2 - size / 2 + x;
                rect.y = vp.h / 2 - size / 2 + y;
            }
            else
            {
                rect.x = size / 2 + x;
                rect.y = size / 2 + y;
            }

            SDL_SetRenderDrawColor(*renptr, col.r, col.g, col.b, col.a);
            SDL_RenderFillRect(*renptr, &rect);
        }

        void drawLine(int x1, int y1, int x2, int y2, SDL_Color col)
        {
            SDL_SetRenderDrawColor(*renptr, col.r, col.g, col.b, col.a);
            SDL_RenderDrawLine(*renptr, x1, y1, x2, y2);
        }

        void drawText(int x, int y, std::string text, Font font, SDL_Color col, bool centred)
        {
            SDL_Surface* sm = TTF_RenderText_Blended(font == Mono ? monoFont : serifFont, text.c_str(), col);
            SDL_Texture* m = SDL_CreateTextureFromSurface(*renptr, sm);

            SDL_Rect rec;
            if (centred)
            {
                SDL_Rect vp;
                SDL_RenderGetViewport(*renptr, &vp);
                rec.x = vp.w / 2 - sm->w / 2 + x;
                rec.y = vp.h / 2 - sm->h / 2 + y;
            }
            else
            {
                rec.x = sm->w / 2 + x;
                rec.y = sm->h / 2 + y;
            }
            rec.w = sm->w;
            rec.h = sm->h;

            SDL_RenderCopy(*renptr, m, nullptr, &rec);
            SDL_FreeSurface(sm);
            SDL_DestroyTexture(m);
        }

        void drawTextWrapped(int x, int y, std::string text, Font font, SDL_Color col, int wrap, bool centred)
        {
            SDL_Surface* sm = TTF_RenderText_Blended_Wrapped(font == Mono ? monoFont : serifFont, text.c_str(), col, wrap);
            SDL_Texture* m = SDL_CreateTextureFromSurface(*renptr, sm);

            SDL_Rect rec;
            if (centred)
            {
                SDL_Rect vp;
                SDL_RenderGetViewport(*renptr, &vp);
                rec.x = vp.w / 2 - sm->w / 2 + x;
                rec.y = vp.h / 2 - sm->h / 2 + y;
            }
            else
            {
                rec.x = x;
                rec.y = y;
            }
            rec.w = sm->w;
            rec.h = sm->h;

            SDL_RenderCopy(*renptr, m, nullptr, &rec);
            SDL_FreeSurface(sm);
            SDL_DestroyTexture(m);
        }

        void drawFrame(int x, int y, int w, int h, SDL_Color col)
        {
            SDL_SetRenderDrawColor(*renptr, col.r, col.g, col.b, col.a);
            //SDL_SetRenderDrawBlendMode(*renptr, SDL_BLENDMODE_BLEND);
            SDL_Rect vp;
            SDL_RenderGetViewport(*renptr, &vp);

            SDL_Rect rec;
            rec.x = vp.w / 2 - w / 2 + x;
            rec.y = vp.h / 2 - h / 2 + y;
            rec.w = w;
            rec.h = h;

            SDL_RenderFillRect(*renptr, &rec);
            //SDL_SetRenderDrawBlendMode(*renptr, SDL_BLENDMODE_NONE);
        }
    }
}
