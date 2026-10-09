#pragma once

#include "Object.h"

class Star : public Object
{
public:
    Star(Vector position);
    int draw() override;
    int eventHandler(const Event* event) override;
};