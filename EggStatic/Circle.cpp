#include "Circle.h"

Circle::Circle(Vector position)
    : Object(position)
{
    setSprite("test");
}

int Circle::draw()
{
    return Object::draw();
}