#pragma once

#include <vector>
#include "Object.h"

class ObjectList
{
public:
    // Add and remove Objecs from list
    void add(Object* object);
    void remove(Object* object);

    Object* operator[](int index);
    int getCount() const;


private:
    // Vector Object
    std::vector<Object*> m_objects;
};
