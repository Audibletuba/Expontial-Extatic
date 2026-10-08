#ifndef MOUSE_CURSOR_H
#define MOUSE_CURSOR_H

#include "Object.h"

class MouseCursor : public Object
{
public:
    MouseCursor(Vector position);

    int draw() override;
};

#endif