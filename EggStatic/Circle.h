#include "Object.h"

class Circle : public Object
{
public:
    Circle(Vector position);

    int draw() override;
};