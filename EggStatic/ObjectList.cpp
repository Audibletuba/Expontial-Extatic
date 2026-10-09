#include "ObjectList.h"

void ObjectList::add(Object* object)
{
    // pushes object into list
    m_objects.push_back(object);
}

void ObjectList::remove(Object* object)
{
    // removes only matching objects
    for (int i = 0; i < m_objects.size(); i++)
    {
        if (m_objects[i] == object)
        {
            m_objects.erase(m_objects.begin() + i);
            return;
        }
    }
}

// Object List
Object* ObjectList::operator[](int index)
{
    if (index < 0 || index >= static_cast<int>(m_objects.size()))
    {
        return nullptr;
    }

    return m_objects[index];
}


// Get Count
int ObjectList::getCount() const
{
    return static_cast<int>(m_objects.size());
}