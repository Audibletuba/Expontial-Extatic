#pragma once
#include "Clock.h"
#include <Windows.h>

class Clock
{
public:
    Clock();

    void start();
    long getElapsedTime();
    long restart();

private:
    // system Time
    SYSTEMTIME m_startTime;
};