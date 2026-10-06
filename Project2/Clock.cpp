#include "Clock.h"

Clock::Clock()
{
    start();
}

void Clock::start()
{
    // start the timing
    GetLocalTime(&m_startTime);
}

long Clock::getElapsedTime()
{
    // use system time to recieve the time spent 
    SYSTEMTIME now;
    GetLocalTime(&now);
    // Long variables ready for delta time
    long nowDay = now.wDay;
    long startDay = m_startTime.wDay;

    long nowHour = now.wHour;
    long startHour = m_startTime.wHour;

    long nowMin = now.wMinute;
    long startMin = m_startTime.wMinute;

    long nowSec = now.wSecond;
    long startSec = m_startTime.wSecond;

    long nowMs = now.wMilliseconds;
    long startMs = m_startTime.wMilliseconds;

    // individual deltas computation

    long delta_day = nowDay - startDay;
    long delta_hour = nowHour - startHour;
    long delta_min = nowMin - startMin;
    long delta_sec = nowSec - startSec;
    long delta_ms = nowMs - startMs;

        // Scale deltas into total milliseconds
        long elapsed_time = delta_ms
            + (delta_sec * 1000)
            + (delta_min * 60 * 1000)
            + (delta_hour * 60 * 60 * 1000)
            + (delta_day * 24 * 60 * 60 * 1000);

        return elapsed_time;
}


long Clock::restart()
{
    // returns the total time elapsed and restarts
    long elapsed = getElapsedTime();
    GetLocalTime(&m_startTime);
    return elapsed;
}
