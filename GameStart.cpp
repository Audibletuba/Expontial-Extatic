//System

//Engine
#include "LogManager.h"
#include "EventKeyboard.h"
#include "GameManager.h"

//Game
#include "GameStart.h"

namespace df
{
    /// @brief Default constructor
    GameStart::GameStart()
    {
        setType("GameStart");

        registerInterest(KEYBOARD_EVENT);
    }

    /// @brief handles the keyboards events to start the game
    /// @param p_e 
    /// @return 0 if ignored, 1 if else
    int GameStart::eventHandler(const Event *p_e)
    {
        if(p_e->getType() == KEYBOARD_EVENT)
        {
            EventKeyboard *pKeyEvent = (EventKeyboard *) p_e;

            switch (pKeyEvent->getKey())
            {
                case Keyboard::P:
                    start();
                    break;
                case Keyboard::Q:   
                    GM.setGameOver();
                    break;
                default:
                    break;
            }
            return 1;
        }

        return 0;
    }

    /// @brief Runs the startup of the game 
    void GameStart::start()
    {

    }

}//End of namespace df