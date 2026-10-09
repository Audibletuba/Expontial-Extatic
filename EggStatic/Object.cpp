#include "Object.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "Vector.h"
#include "ResourceManager.h"
#include "Sprite.h"

#include <iostream>

// Initialize static auto-increment ID counter
int Object::s_next_id = 0;

// Default Constructor: Auto-increments unique ID and does NOT self-add to world
Object::Object(Vector position, int type, int id)
    : m_position(position), m_type(type),
    m_delete_flag(false), m_altitude(0),
    m_solidness(SOLID), m_direction(), m_speed(0.0f)
{
    if (id < 0)
    {
        m_id = s_next_id++;
    }
    else
    {
        m_id = id;

        if (id >= s_next_id)
        {
            s_next_id = id + 1;
        }
    }
}


// Get Objects Position
Vector Object::getPosition() const
{
    return m_position;
}

// Sets Objects Position
void Object::setPosition(Vector position)
{
    m_position = position;
}

// Get Types
int Object::getType() const
{
    return m_type;
}

// Get IDs
int Object::getID() const
{
    return m_id;
}

void Object::addToWorld()
{
    WorldManager::getInstance().addObject(this);
}

void Object::removeFromWorld()
{
    WorldManager::getInstance().removeObject(this);
}

int Object::eventHandler(const Event* event)
{
    if (event == nullptr)
    {
        return 1;
    }

    std::cout << "Object " << getID()
        << " received event: "
        << event->getType()
        << std::endl;

    return 0;
}


void Object::setDeleteFlag(bool flag)
{
    m_delete_flag = flag;
}

bool Object::getDeleteFlag() const
{
    return m_delete_flag;
}

int Object::draw()
{
    // Draw Object Animation.
    Vector pos = getPosition();

    return m_animation.draw(pos);
}

int Object::setAltitude(int new_altitude)
{
    if (new_altitude < 0 || new_altitude > MAX_ALTITUDE)
    {
        return -1;
    }

    m_altitude = new_altitude;

    return 0;
}

int Object::getAltitude() const
{
    return m_altitude;
}

void Object::setVelocity(Vector new_velocity)
{
    m_speed = new_velocity.getMagnitude();

    m_direction = new_velocity;
    m_direction.normalize();
}

Vector Object::getVelocity() const
{
    Vector velocity = m_direction;
    velocity.scale(m_speed);

    return velocity;
}


Vector Object::predictPosition() const
{
    Vector new_pos = m_position + getVelocity();

    return new_pos;
}

void Object::update()
{
    // Predict new position.
    Vector new_pos = predictPosition();

    // Move Object.
    WorldManager::getInstance().moveObject(this, new_pos);
}

bool Object::isSolid() const
{
    return m_solidness == SOLID;
}

void Object::setSolidness(Solidness new_solidness)
{
    if (new_solidness == SOLID ||
        new_solidness == SOFT ||
        new_solidness == SPECTRAL)
    {
        m_solidness = new_solidness;
    }
}

Solidness Object::getSolidness() const
{
    return m_solidness;
}



int Object::setSprite(std::string sprite_label)
{
    Sprite* p_sprite =
        ResourceManager::getInstance().getSprite(sprite_label);

    if (p_sprite == nullptr)
    {
        return -1;
    }

    m_animation.setSprite(p_sprite);

    float width = p_sprite->getWidth();
    float height = p_sprite->getHeight();

    // Set Object dimensions to match Sprite.
    m_width = p_sprite->getWidth();
    m_height = p_sprite->getHeight();

    // Bounding box corner is relative to Object position.
    Vector corner(
        -width / 2.0f,
        -height / 2.0f
    );

    m_box.setCorner(corner);
    m_box.setHorizontal(width);
    m_box.setVertical(height);

    return 0;
}

void Object::setAnimation(Animation new_animation)
{
    m_animation = new_animation;

    Sprite* p_sprite = m_animation.getSprite();

    if (p_sprite != nullptr)
    {
        // Set Object size to match Sprite.
        m_width = p_sprite->getWidth();
        m_height = p_sprite->getHeight();
    }
}

Animation Object::getAnimation() const
{
    return m_animation;
}

void Object::setBox(Box new_box)
{
    m_box = new_box;
}

Box Object::getBox() const
{
    return m_box;
}
