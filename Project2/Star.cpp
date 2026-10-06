#include "Star.h"
#include "DisplayManager.h"
#include "EventStep.h"

Star::Star(Vector position)
    : Object(position)
{
}

int Star::draw()
{
    DisplayManager::getInstance().drawCh(
        getPosition(),
        '*',
        YELLOW

    );
    return 1;
}
int Star::eventHandler(const Event* event)
{
    if (event == nullptr)
    {
        return 0;
    }

    static int counter = 0;

    counter++;

    if (counter >= 30)
    {
        if (getAltitude() == 0)
        {
            setAltitude(1);
        }
        else
        {
            setAltitude(0);
        }

        counter = 0;
    }
    return 1;
}