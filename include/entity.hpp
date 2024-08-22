#pragma once
#include "drawable.hpp"
#include <SDL2/SDL_render.h>

namespace arc
{
    // Entity base class
    class Entity : public Drawable
    {
    protected:
        float m_x, m_y;
        float m_w, m_h; // hitbox

    public:
        Entity(float x, float y, float w, float h);

    public:
        float getX();
        float getY();

        float getW();
        float getH();

    public:
        void setX(float x);
        void setY(float y);
        void setPosition(float x, float y);
        void move(float x, float y);
        void moveX(float x);
        void moveY(float y);

        void setW(float w);
        void setH(float h);
        void setSize(float w, float h);

        bool aabb(Entity other);

        virtual void tick(float dt) {};
        virtual void draw(SDL_Renderer* ren) const {};
    };
}
