#pragma once

#include "Manager.h"
#include "Clock.h"

class GameManager : public Manager
{
private:
    Clock m_clock;
    bool m_game_over;

    //Singelton
    GameManager();

    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;

public:
    static GameManager& getInstance();

    // startup shutDown functions=
    int startUp();
    void shutDown();

    void run();
};


