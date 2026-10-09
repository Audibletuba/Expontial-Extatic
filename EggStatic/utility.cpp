#include "utility.h"

#include <cmath>

// Return true if two positions intersect, else false.
bool positionsIntersect(Vector p1, Vector p2)
{
    // Check if X positions are within 1.
    if (std::abs(p1.getX() - p2.getX()) <= 1 &&
        // Check if Y positions are within 1.
        std::abs(p1.getY() - p2.getY()) <= 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool boxIntersectsBox(Box A, Box B)
{
    // Get corners of both boxes.
    Vector A_corner = A.getCorner();
    Vector B_corner = B.getCorner();

    // Box A boundaries.
    float Ax1 = A_corner.getX();
    float Ay1 = A_corner.getY();
    float Ax2 = Ax1 + A.getHorizontal();
    float Ay2 = Ay1 + A.getVertical();

    // Box B boundaries.
    float Bx1 = B_corner.getX();
    float By1 = B_corner.getY();
    float Bx2 = Bx1 + B.getHorizontal();
    float By2 = By1 + B.getVertical();

    // Test horizontal overlap.
    bool x_overlap =
        (Bx1 <= Ax1 && Ax1 <= Bx2) ||
        (Ax1 <= Bx1 && Bx1 <= Ax2);

    // Test vertical overlap.
    bool y_overlap =
        (By1 <= Ay1 && Ay1 <= By2) ||
        (Ay1 <= By1 && By1 <= Ay2);

    // Boxes intersect only if both dimensions overlap.
    if (x_overlap && y_overlap)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Box getWorldBox(const Object* p_o)
{
    return getWorldBox(p_o, p_o->getPosition());
}

Box getWorldBox(const Object* p_o, Vector where)
{
    Box box = p_o->getBox();

    Vector corner = box.getCorner();

    corner.setX(
        corner.getX() + where.getX()
    );

    corner.setY(
        corner.getY() + where.getY()
    );

    box.setCorner(corner);

    return box;
}

bool valueInRange(float value, float min, float max)
{
    return (value >= min && value <= max);
}