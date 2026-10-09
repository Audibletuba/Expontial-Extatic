#include "InputManager.h"
#include "DisplayManager.h"
#include "WorldManager.h"

#include <iostream>

InputManager::InputManager()
{
}

InputManager& InputManager::getInstance()
{
    static InputManager instance;
    return instance;
}

int InputManager::startUp()
{
    if (!DisplayManager::getInstance().getIsRunning())
    {
        return 1;
    }

    return Manager::startUp();
}

void InputManager::shutDown()
{
    Manager::shutDown();
}

void InputManager::getInput()
{
    sf::RenderWindow* window =
        DisplayManager::getInstance().getWindow();

    if (window == nullptr)
    {
        return;
    }

    while (auto event = window->pollEvent())
    {

        // Window close event.
        if (event->is<sf::Event::Closed>())
        {
            window->close();
            continue;
        }

        // Keyboard pressed.
        if (const auto* key_pressed =
            event->getIf<sf::Event::KeyPressed>())
        {
            if (key_pressed->scancode == sf::Keyboard::Scan::A)
            {
                EventKeyboard keyboard_event;

                keyboard_event.setKey(Keyboard::A);
                keyboard_event.setKeyboardAction(KEY_PRESSED);

                WorldManager::getInstance().onEvent(&keyboard_event);
                std::cout << "A pressed" << std::endl;
            }

            if (key_pressed->scancode == sf::Keyboard::Scan::B)
            {
                EventKeyboard keyboard_event;

                keyboard_event.setKey(Keyboard::B);
                keyboard_event.setKeyboardAction(KEY_PRESSED);

                WorldManager::getInstance().onEvent(&keyboard_event);
                std::cout << "B pressed" << std::endl;
            }

            if (key_pressed->scancode == sf::Keyboard::Scan::C)
            {
                EventKeyboard keyboard_event;

                keyboard_event.setKey(Keyboard::C);
                keyboard_event.setKeyboardAction(KEY_PRESSED);

                WorldManager::getInstance().onEvent(&keyboard_event);
                std::cout << "C pressed" << std::endl;
            }
            if (key_pressed->scancode == sf::Keyboard::Scan::D)
            {
                EventKeyboard keyboard_event;

                keyboard_event.setKey(Keyboard::D);
                keyboard_event.setKeyboardAction(KEY_PRESSED);

                WorldManager::getInstance().onEvent(&keyboard_event);
                std::cout << "D pressed" << std::endl;
            }
            if (key_pressed->scancode == sf::Keyboard::Scan::Q)
            {
                EventKeyboard keyboard_event;

                keyboard_event.setKey(Keyboard::Q);
                keyboard_event.setKeyboardAction(KEY_PRESSED);

                WorldManager::getInstance().onEvent(&keyboard_event);
                std::cout << "Q pressed" << std::endl;
            }
            if (key_pressed->scancode == sf::Keyboard::Scan::E)
            {
                EventKeyboard keyboard_event;

                keyboard_event.setKey(Keyboard::E);
                keyboard_event.setKeyboardAction(KEY_PRESSED);

                WorldManager::getInstance().onEvent(&keyboard_event);
                std::cout << "E pressed" << std::endl;
            }
            if (key_pressed->scancode == sf::Keyboard::Scan::F)
            {
                EventKeyboard keyboard_event;

                keyboard_event.setKey(Keyboard::F);
                keyboard_event.setKeyboardAction(KEY_PRESSED);

                WorldManager::getInstance().onEvent(&keyboard_event);
                std::cout << "F pressed" << std::endl;
            }
            if (key_pressed->scancode == sf::Keyboard::Scan::W)
            {
                EventKeyboard keyboard_event;

                keyboard_event.setKey(Keyboard::W);
                keyboard_event.setKeyboardAction(KEY_PRESSED);

                WorldManager::getInstance().onEvent(&keyboard_event);
                std::cout << "W pressed" << std::endl;
            }
            if (key_pressed->scancode == sf::Keyboard::Scan::S)
            {
                EventKeyboard keyboard_event;

                keyboard_event.setKey(Keyboard::S);
                keyboard_event.setKeyboardAction(KEY_PRESSED);

                WorldManager::getInstance().onEvent(&keyboard_event);
                std::cout << "S pressed" << std::endl;
            }
            if (key_pressed->scancode == sf::Keyboard::Scan::Space)
            {
                EventKeyboard keyboard_event;

                keyboard_event.setKey(Keyboard::SPACE);
                keyboard_event.setKeyboardAction(KEY_PRESSED);

                WorldManager::getInstance().onEvent(&keyboard_event);
                std::cout << "SPACE pressed" << std::endl;
            }
            if (key_pressed->scancode == sf::Keyboard::Scan::Tab)
            {
                EventKeyboard keyboard_event;

                keyboard_event.setKey(Keyboard::TAB);
                keyboard_event.setKeyboardAction(KEY_PRESSED);

                WorldManager::getInstance().onEvent(&keyboard_event);
                std::cout << "TAB pressed" << std::endl;
            }
            if (key_pressed->scancode == sf::Keyboard::Scan::Enter)
            {
                EventKeyboard keyboard_event;
                keyboard_event.setKey(Keyboard::RETURN);
                keyboard_event.setKeyboardAction(KEY_PRESSED);

                WorldManager::getInstance().onEvent(&keyboard_event);
                std::cout << "RETURN pressed" << std::endl;
            }

            if (key_pressed->scancode == sf::Keyboard::Scan::Escape)
            {
                EventKeyboard keyboard_event;
                keyboard_event.setKey(Keyboard::ESCAPE);
                keyboard_event.setKeyboardAction(KEY_PRESSED);

                WorldManager::getInstance().onEvent(&keyboard_event);
                std::cout << "ESCAPE pressed" << std::endl;
            }

            if (key_pressed->scancode == sf::Keyboard::Scan::Up)
            {
                EventKeyboard keyboard_event;
                keyboard_event.setKey(Keyboard::UPARROW);
                keyboard_event.setKeyboardAction(KEY_PRESSED);

                WorldManager::getInstance().onEvent(&keyboard_event);
                std::cout << "UP pressed" << std::endl;
            }

            if (key_pressed->scancode == sf::Keyboard::Scan::Down)
            {
                EventKeyboard keyboard_event;
                keyboard_event.setKey(Keyboard::DOWNARROW);
                keyboard_event.setKeyboardAction(KEY_PRESSED);

                WorldManager::getInstance().onEvent(&keyboard_event);
                std::cout << "DOWN pressed" << std::endl;
            }

            if (key_pressed->scancode == sf::Keyboard::Scan::Left)
            {
                EventKeyboard keyboard_event;
                keyboard_event.setKey(Keyboard::LEFTARROW);
                keyboard_event.setKeyboardAction(KEY_PRESSED);

                WorldManager::getInstance().onEvent(&keyboard_event);
                std::cout << "LEFT pressed" << std::endl;
            }

            if (key_pressed->scancode == sf::Keyboard::Scan::Right)
            {
                EventKeyboard keyboard_event;
                keyboard_event.setKey(Keyboard::RIGHTARROW);
                keyboard_event.setKeyboardAction(KEY_PRESSED);

                WorldManager::getInstance().onEvent(&keyboard_event);
                std::cout << "RIGHT pressed" << std::endl;
            }
        }

        // Keyboard released.
        if (const auto* key_released =
            event->getIf<sf::Event::KeyReleased>())
        {
            if (key_released->scancode == sf::Keyboard::Scan::A)
            {
                EventKeyboard keyboard_event;

                keyboard_event.setKey(Keyboard::A);
                keyboard_event.setKeyboardAction(KEY_RELEASED);

                WorldManager::getInstance().onEvent(&keyboard_event);
                std::cout << "A released" << std::endl;
            }

            if (key_released->scancode == sf::Keyboard::Scan::B)
            {
                EventKeyboard keyboard_event;

                keyboard_event.setKey(Keyboard::B);
                keyboard_event.setKeyboardAction(KEY_RELEASED);

                WorldManager::getInstance().onEvent(&keyboard_event);
                std::cout << "B released" << std::endl;
            }

            if (key_released->scancode == sf::Keyboard::Scan::C)
            {
                EventKeyboard keyboard_event;

                keyboard_event.setKey(Keyboard::C);
                keyboard_event.setKeyboardAction(KEY_RELEASED);

                WorldManager::getInstance().onEvent(&keyboard_event);
                std::cout << "C released" << std::endl;
            }
            if (key_released->scancode == sf::Keyboard::Scan::D)
            {
                EventKeyboard keyboard_event;

                keyboard_event.setKey(Keyboard::D);
                keyboard_event.setKeyboardAction(KEY_RELEASED);

                WorldManager::getInstance().onEvent(&keyboard_event);
                std::cout << "D released" << std::endl;
            }
            if (key_released->scancode == sf::Keyboard::Scan::Q)
            {
                EventKeyboard keyboard_event;

                keyboard_event.setKey(Keyboard::Q);
                keyboard_event.setKeyboardAction(KEY_RELEASED);

                WorldManager::getInstance().onEvent(&keyboard_event);
                std::cout << "Q released" << std::endl;
            }
            if (key_released->scancode == sf::Keyboard::Scan::E)
            {
                EventKeyboard keyboard_event;

                keyboard_event.setKey(Keyboard::E);
                keyboard_event.setKeyboardAction(KEY_RELEASED);

                WorldManager::getInstance().onEvent(&keyboard_event);
                std::cout << "E released" << std::endl;
            }
            if (key_released->scancode == sf::Keyboard::Scan::F)
            {
                EventKeyboard keyboard_event;

                keyboard_event.setKey(Keyboard::F);
                keyboard_event.setKeyboardAction(KEY_RELEASED);

                WorldManager::getInstance().onEvent(&keyboard_event);
                std::cout << "F released" << std::endl;
            }
            if (key_released->scancode == sf::Keyboard::Scan::W)
            {
                EventKeyboard keyboard_event;

                keyboard_event.setKey(Keyboard::W);
                keyboard_event.setKeyboardAction(KEY_RELEASED);

                WorldManager::getInstance().onEvent(&keyboard_event);
                std::cout << "W released" << std::endl;
            }
            if (key_released->scancode == sf::Keyboard::Scan::S)
            {
                EventKeyboard keyboard_event;

                keyboard_event.setKey(Keyboard::S);
                keyboard_event.setKeyboardAction(KEY_RELEASED);

                WorldManager::getInstance().onEvent(&keyboard_event);
                std::cout << "S released" << std::endl;
            }
            if (key_released->scancode == sf::Keyboard::Scan::Space)
            {
                EventKeyboard keyboard_event;

                keyboard_event.setKey(Keyboard::SPACE);
                keyboard_event.setKeyboardAction(KEY_RELEASED);

                WorldManager::getInstance().onEvent(&keyboard_event);
                std::cout << "SPACE released" << std::endl;
            }
            if (key_released->scancode == sf::Keyboard::Scan::Tab)
            {
                EventKeyboard keyboard_event;

                keyboard_event.setKey(Keyboard::TAB);
                keyboard_event.setKeyboardAction(KEY_RELEASED);

                WorldManager::getInstance().onEvent(&keyboard_event);
                std::cout << "TAB released" << std::endl;
            }
            if (key_released->scancode == sf::Keyboard::Scan::Enter)
            {
                EventKeyboard keyboard_event;
                keyboard_event.setKey(Keyboard::RETURN);
                keyboard_event.setKeyboardAction(KEY_RELEASED);

                WorldManager::getInstance().onEvent(&keyboard_event);
                std::cout << "RETURN released" << std::endl;
            }

            if (key_released->scancode == sf::Keyboard::Scan::Escape)
            {
                EventKeyboard keyboard_event;
                keyboard_event.setKey(Keyboard::ESCAPE);
                keyboard_event.setKeyboardAction(KEY_RELEASED);

                WorldManager::getInstance().onEvent(&keyboard_event);
                std::cout << "ESCAPE released" << std::endl;
            }

            if (key_released->scancode == sf::Keyboard::Scan::Up)
            {
                EventKeyboard keyboard_event;
                keyboard_event.setKey(Keyboard::UPARROW);
                keyboard_event.setKeyboardAction(KEY_RELEASED);

                WorldManager::getInstance().onEvent(&keyboard_event);
                std::cout << "UP released" << std::endl;
            }

            if (key_released->scancode == sf::Keyboard::Scan::Down)
            {
                EventKeyboard keyboard_event;
                keyboard_event.setKey(Keyboard::DOWNARROW);
                keyboard_event.setKeyboardAction(KEY_RELEASED);

                WorldManager::getInstance().onEvent(&keyboard_event);
                std::cout << "DOWN released" << std::endl;
            }

            if (key_released->scancode == sf::Keyboard::Scan::Left)
            {
                EventKeyboard keyboard_event;
                keyboard_event.setKey(Keyboard::LEFTARROW);
                keyboard_event.setKeyboardAction(KEY_RELEASED);

                WorldManager::getInstance().onEvent(&keyboard_event);
                std::cout << "LEFT released" << std::endl;
            }

            if (key_released->scancode == sf::Keyboard::Scan::Right)
            {
                EventKeyboard keyboard_event;
                keyboard_event.setKey(Keyboard::RIGHTARROW);
                keyboard_event.setKeyboardAction(KEY_RELEASED);

                WorldManager::getInstance().onEvent(&keyboard_event);
                std::cout << "RIGHT released" << std::endl;
            }
        }
        // Mouse button pressed.
        if (const auto* mouse_pressed =
            event->getIf<sf::Event::MouseButtonPressed>())
        {
            Vector mouse_position(
                mouse_pressed->position.x,
                mouse_pressed->position.y
            );

            // Left mouse button.
            if (mouse_pressed->button == sf::Mouse::Button::Left)
            {
                EventMouse mouse_event;

                mouse_event.setMouseAction(CLICKED);
                mouse_event.setMouseButton(Mouse::LEFT);
                mouse_event.setMouseXY(mouse_position);

                WorldManager::getInstance().onEvent(&mouse_event);
                std::cout << "Left mouse clicked at ("
                    << mouse_pressed->position.x
                    << ", "
                    << mouse_pressed->position.y
                    << ")"
                    << std::endl;
            }

            // Right mouse button.
            if (mouse_pressed->button == sf::Mouse::Button::Right)
            {
                EventMouse mouse_event;

                mouse_event.setMouseAction(CLICKED);
                mouse_event.setMouseButton(Mouse::RIGHT);
                mouse_event.setMouseXY(mouse_position);

                WorldManager::getInstance().onEvent(&mouse_event);
                std::cout << "Right mouse clicked at ("
                    << mouse_pressed->position.x
                    << ", "
                    << mouse_pressed->position.y
                    << ")"
                    << std::endl;
            }

            // Middle mouse button.
            if (mouse_pressed->button == sf::Mouse::Button::Middle)
            {
                EventMouse mouse_event;

                mouse_event.setMouseAction(CLICKED);
                mouse_event.setMouseButton(Mouse::MIDDLE);
                mouse_event.setMouseXY(mouse_position);

                WorldManager::getInstance().onEvent(&mouse_event);
                std::cout << "Middle mouse clicked at ("
                    << mouse_pressed->position.x
                    << ", "
                    << mouse_pressed->position.y
                    << ")"
                    << std::endl;
            }
        }
    }
}
 