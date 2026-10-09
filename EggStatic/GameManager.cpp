#include "GameManager.h"
#include "WorldManager.h"
#include "EventStep.h"
#include "DisplayManager.h"
#include "InputManager.h"



GameManager::GameManager()
{
    m_game_over = false;
}
// Singleton Instance
GameManager& GameManager::getInstance()
{
    static GameManager instance;
    return instance;
}

// startup function
int GameManager::startUp()
{
    m_game_over = false;

    if (DisplayManager::getInstance().startUp() != 0)
    {
        return 1;
    }

    if (InputManager::getInstance().startUp() != 0)
    {
        DisplayManager::getInstance().shutDown();
        return 1;
    }

    WorldManager::getInstance().startUp();

    return 0;
}

// shutDown function
void GameManager::shutDown()
{
    m_game_over = true;
}
void GameManager::run()
{
    int step_count = 0;

    // Target duration per frame at 30 Hz in milliseconds (~33 ms)
    const long TARGET_TIME = 33;

    while (!m_game_over)
    {
        // Start timing
        m_clock.restart();

        // Get keyboard and mouse input
        InputManager::getInstance().getInput();

        // Send step event to every object in the world
        EventStep step_event(step_count);

        ObjectList& objects =
            WorldManager::getInstance().getAllObjects();

        for (int i = 0; i < objects.getCount(); i++)
        {
            Object* object = objects[i];

            if (object != nullptr)
            {
                object->eventHandler(&step_event);
                object->update();

            }
        }

        // Process object deletions
        WorldManager::getInstance().processDeletes();

        // Draw all objects in the world
        WorldManager::getInstance().draw();

        // Display the completed frame
        DisplayManager::getInstance().swapBuffers();

        step_count++;

        // Measure loop_time
        long loop_time = m_clock.getElapsedTime();

        if (loop_time < 0)
        {
            loop_time = 0;
        }

        // maintain 30 hrtz by sleeping rest of refresh
        long sleepTime = TARGET_TIME - loop_time;

        if (sleepTime > 0)
        {
            Sleep(sleepTime);
        }
    }
}
