#include "entity.hpp"

namespace arc
{
    Entity::Entity(float x, float y, float w, float h)
        : m_x(x), m_y(y), m_w(w), m_h(h)
    {
        
    }

    float Entity::getX()
    {
        return m_x;
    }

    float Entity::getY()
    {
        return m_y;
    }

    float Entity::getW()
    {
        return m_w;
    }

    float Entity::getH()
    {
        return m_h;
    }

    void Entity::setX(float x)
    {
        m_x = x;
    }
    
    void Entity::setY(float y)
    {
        m_y = y;
    }
    
    void Entity::setPosition(float x, float y)
    {
        m_x = x; m_y = y;
    }

    void Entity::move(float x, float y)
    {
        m_x += x; m_y += y;
    }

    void Entity::moveX(float x)
    {
        m_x += x;
    }

    void Entity::moveY(float y)
    {
        m_y += y;
    }

    void Entity::setW(float w)
    {
        m_w = w;
    }
    
    void Entity::setH(float h)
    {
        m_h = h;
    }
    
    void Entity::setSize(float w, float h)
    {
        m_w = w; m_h = h;
    }

    // Entity collision using axis aligned bounding boxes (AABB)
    bool Entity::aabb(Entity other)
    {
        return (m_x + m_w >= other.getX()) &&
            (m_x <= other.getX() + other.getW()) &&
            (m_y + m_h >= other.getY()) &&
            (m_y <= other.getY() + other.getH());
    }
}
