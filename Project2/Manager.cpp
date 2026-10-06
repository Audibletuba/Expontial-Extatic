#include "Manager.h"
#include "WorldManager.h"

Manager::Manager()
    : isRunning(false)
{
}

// startUp
int Manager::startUp()
{
    if (isRunning)
        return 1;

    isRunning = true;
    return 0;
}

// shutDown
void Manager::shutDown()
{
    if (!isRunning)
        return;

    isRunning = false;
}

// getIsRunning
bool Manager::getIsRunning() const
{
    return isRunning;
}

int Manager::onEvent(const Event* event) const
{
    int count = 0;

    ObjectList& all_objects =
        WorldManager::getInstance().getAllObjects();

    for (int i = 0; i < all_objects.getCount(); i++)
    {
        if (all_objects[i]->eventHandler(event))
        {
            count++;
        }
    }

    return count;
}