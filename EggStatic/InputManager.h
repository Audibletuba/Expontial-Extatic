#pragma once

#include "Manager.h"
#include "EventKeyboard.h"
#include "EventMouse.h"

class InputManager : public Manager
{
private:
    InputManager();

public:
    static InputManager& getInstance();

    int startUp();
    void shutDown();

    void getInput();
};