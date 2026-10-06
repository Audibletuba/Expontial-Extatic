#include "WorldManager.h"
#include "utility.h"
#include "EventCollision.h"
#include "EventOut.h"
#include "DisplayManager.h"
WorldManager::WorldManager()
{
}

WorldManager& WorldManager::getInstance()
{
    static WorldManager instance;
    return instance;
}

void WorldManager::startUp()
{
    Manager::startUp();
}

void WorldManager::shutDown()
{
    Manager::shutDown();
}

void WorldManager::addObject(Object* object)
{
    m_object_list.add(object);
}

void WorldManager::removeObject(Object* object)
{
    m_object_list.remove(object);
}

ObjectList& WorldManager::getAllObjects()
{
    return m_object_list;
}

void WorldManager::markForDelete(Object* object)
{
    if (object != nullptr)
    {
        object->setDeleteFlag(true);
    }
}

void WorldManager::processDeletes()
{
    for (int i = m_object_list.getCount() - 1; i >= 0; i--)
    {
        Object* object = m_object_list[i];

        if (object != nullptr && object->getDeleteFlag())
        {
            m_object_list.remove(object);
        }
    }

}

void WorldManager::draw()
{
    Box view = getView();

    for (int alt = 0; alt <= MAX_ALTITUDE; alt++)
    {
        for (int i = 0; i < m_object_list.getCount(); i++)
        {
            Object* p_o = m_object_list[i];

            if (p_o->getAltitude() == alt)
            {
                // Bounding box coordinates are relative to Object,
                // so convert to world coordinates.
                Box temp_box = getWorldBox(p_o);

                // Only draw if Object would be visible on window.
                if (boxIntersectsBox(temp_box, view))
                {
                    p_o->draw();
                }
            }
        }
    }
}

ObjectList WorldManager::getCollisions(const Object* p_o, Vector where)
{
    ObjectList collision_list;

    for (int i = 0; i < m_object_list.getCount(); i++)
    {
        Object* p_temp_o = m_object_list[i];

        if (p_temp_o != p_o)
        {
            // World position bounding box for object at where.
            Box b = getWorldBox(p_o, where);

            // World position bounding box for other object.
            Box b_temp = getWorldBox(p_temp_o);

            if (boxIntersectsBox(b, b_temp)
                && p_temp_o->isSolid())
            {
                collision_list.add(p_temp_o);
            }
        }
    }

    return collision_list;
}

int WorldManager::moveObject(Object* p_o, Vector where)
{
    // Need to be solid for collisions.
    if (p_o->isSolid())
    {
        ObjectList collision_list = getCollisions(p_o, where);

        if (collision_list.getCount() > 0)
        {
            bool do_move = true;

            for (int i = 0; i < collision_list.getCount(); i++)
            {
                Object* p_temp_o = collision_list[i];

                EventCollision collision_event(
                    p_o,
                    p_temp_o,
                    where
                );

                p_o->eventHandler(&collision_event);
                p_temp_o->eventHandler(&collision_event);

                if (p_o->isSolid() && p_temp_o->isSolid())
                {
                    do_move = false;
                }
            }

            if (!do_move)
            {
                return -1;
            }
        }
    }

    // Do move.
    Box orig_box = getWorldBox(p_o);

    p_o->setPosition(where);

    // If view is following this object, adjust view.
    if (p_view_following == p_o)
    {
        setViewPosition(p_o->getPosition());
    }
    Box new_box = getWorldBox(p_o);

    // If object moved from inside to outside world, generate
    // "out of bounds" event.
    if (boxIntersectsBox(orig_box, m_boundary)
        && !boxIntersectsBox(new_box, m_boundary))
    {
        EventOut out_event;
        p_o->eventHandler(&out_event);
    }
    return 0;
}

void WorldManager::setBoundary(Box new_boundary)
{
    m_boundary = new_boundary;
}

Box WorldManager::getBoundary() const
{
    return m_boundary;
}

void WorldManager::setView(Box new_view)
{
    m_view = new_view;
}

Box WorldManager::getView() const
{
    return m_view;
}

void WorldManager::setViewPosition(Vector view_pos)
{
    // Make sure horizontal not out of world boundary.
    float x = view_pos.getX() - m_view.getHorizontal() / 2;

    if (x + m_view.getHorizontal() > m_boundary.getHorizontal())
    {
        x = m_boundary.getHorizontal() - m_view.getHorizontal();
    }

    if (x < 0)
    {
        x = 0;
    }

    // Make sure vertical not out of world boundary.
    float y = view_pos.getY() - m_view.getVertical() / 2;

    if (y + m_view.getVertical() > m_boundary.getVertical())
    {
        y = m_boundary.getVertical() - m_view.getVertical();
    }

    if (y < 0)
    {
        y = 0;
    }

    // Set view.
    Vector new_corner(x, y);
    m_view.setCorner(new_corner);
}

int WorldManager::setViewFollowing(Object* p_new_view_following)
{
    // Set to NULL to turn 'off' following.
    if (p_new_view_following == nullptr)
    {
        p_view_following = nullptr;
        return 0;
    }

    // Make sure p_new_view_following is one of the Objects.
    bool found = false;

    for (int i = 0; i < m_object_list.getCount(); i++)
    {
        if (m_object_list[i] == p_new_view_following)
        {
            found = true;
            break;
        }
    }

    // If found, set following and position view.
    if (found)
    {
        p_view_following = p_new_view_following;
        setViewPosition(p_view_following->getPosition());
        return 0;
    }

    // Not a legitimate Object.
    return -1;
}