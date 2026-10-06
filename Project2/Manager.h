#pragma once

#include "Event.h"

class Manager
{
public:
    Manager();

    // Start and stop the Manager.
    int startUp();
    void shutDown();

    bool getIsRunning() const;

    // Send event to all Objects.
    int onEvent(const Event* event) const;

private:
    bool isRunning;
};