#include "MouseCursor.h"

MouseCursor::MouseCursor(Vector position)
    : Object(position)
{
    setSolidness(SPECTRAL);
    setSprite("pan");

    // Draw the cursor above other game objects.
    setAltitude(4);
}

int MouseCursor::draw()
{
    Object::draw();
    return 0;
}