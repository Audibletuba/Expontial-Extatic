#pragma once

#include "Box.h"
#include "Object.h"

// returns if 2 boxes overlap
bool boxIntersectsBox(Box A, Box B);

// gets box relative to world
Box getWorldBox(const Object* p_o);

Box getWorldBox(const Object* p_o, Vector where);

bool valueInRange(float value, float min, float max);