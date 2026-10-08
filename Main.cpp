#include "DisplayManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"

#include "Player.h"
#include "Enemy.h"
#include "Shop.h"
#include "Button.h"
#include "MouseCursor.h"

#include "EventMouse.h"

#include <iostream>

enum GameScreen
{
    TITLE_SCREEN,
    BATTLE_SCREEN,
    SHOP_SCREEN
};

int main()
{
    DisplayManager& display_manager =
        DisplayManager::getInstance();

    WorldManager& world_manager =
        WorldManager::getInstance();

    ResourceManager& resource_manager =
        ResourceManager::getInstance();

    display_manager.startUp();
    world_manager.startUp();
    resource_manager.startUp();

    world_manager.setBoundary(
        Box(
            Vector(0, 0),
            80,
            24
        )
    );

    world_manager.setView(
        Box(
            Vector(0, 0),
            80,
            24
        )
    );

    resource_manager.loadSprite(
        "Sprites/shop.txt",
        "shop"
    );

    resource_manager.loadSprite(
        "Sprites/attack.txt",
        "attack"
    );

    resource_manager.loadSprite(
        "Sprites/time.txt",
        "timer"
    );

    resource_manager.loadSprite(
        "Sprites/difficulty.txt",
        "difficulty"
    );

    resource_manager.loadSprite(
        "Sprites/money.txt",
        "money"
    );

    resource_manager.loadSprite(
        "Sprites/enemy.txt",
        "enemy"
    );

    resource_manager.loadSprite(
        "Sprites/play.txt",
        "play"
    );

    resource_manager.loadSprite(
        "Sprites/fight.txt",
        "fight"
    );

    resource_manager.loadSprite(
        "Sprites/pan.txt",
        "pan"
    );

    Button* play_button =
        new Button(
            Vector(40, 16),
            "play"
        );

    Player* player =
        new Player(
            Vector(40, 0)
        );

    Enemy* enemy =
        new Enemy(
            Vector(40, 10),
            player->getEnemyHealth()
        );

    Shop* shop =
        new Shop(
            Vector(40, 12)
        );

    Button* fight_button =
        new Button(
            Vector(40, 21),
            "fight"
        );

    MouseCursor* mouse_cursor =
        new MouseCursor(
            Vector(40, 12)
        );

    GameScreen current_screen =
        TITLE_SCREEN;

    Vector mouse_world(40, 12);

    world_manager.addObject(player);
    world_manager.addObject(play_button);
    world_manager.addObject(mouse_cursor);

    while (
        display_manager.getWindow()->isOpen()
        )
    {
        // UPDATE MOUSE POSITION
        sf::Vector2i mouse_pixel =
            sf::Mouse::getPosition(
                *display_manager.getWindow()
            );

        float world_x =
            (
                static_cast<float>(mouse_pixel.x)
                / 1024.0f
                ) * 80.0f;

        float world_y =
            (
                static_cast<float>(mouse_pixel.y)
                / 768.0f
                ) * 24.0f;

        mouse_world =
            Vector(
                world_x,
                world_y
            );

        mouse_cursor->setPosition(
            mouse_world
        );

        // HANDLE EVENTS
        while (
            auto event =
            display_manager.getWindow()->pollEvent()
            )
        {
            if (
                event->is<sf::Event::Closed>()
                )
            {
                display_manager
                    .getWindow()
                    ->close();
            }

            if (
                auto mouse_event =
                event->getIf<
                sf::Event::MouseButtonPressed
                >()
                )
            {
                if (
                    mouse_event->button !=
                    sf::Mouse::Button::Left
                    )
                {
                    continue;
                }

                EventMouse dragonfly_mouse_event;

                dragonfly_mouse_event.setMouseAction(
                    CLICKED
                );

                dragonfly_mouse_event.setMouseButton(
                    Mouse::LEFT
                );

                dragonfly_mouse_event.setMouseXY(
                    mouse_world
                );

                std::cout
                    << "Mouse: "
                    << mouse_world.getX()
                    << ", "
                    << mouse_world.getY()
                    << "\n";

                // TITLE SCREEN
                if (
                    current_screen ==
                    TITLE_SCREEN
                    )
                {
                    play_button->eventHandler(
                        &dragonfly_mouse_event
                    );

                    if (
                        play_button->isClicked()
                        )
                    {
                        play_button->clearClicked();

                        world_manager.removeObject(
                            play_button
                        );

                        world_manager.addObject(
                            enemy
                        );

                        current_screen =
                            BATTLE_SCREEN;

                        enemy->startTimer(
                            player->getEnemyHealth(),
                            player->getBattleTime()
                        );

                        std::cout
                            << "BATTLE STARTED\n";
                    }
                }

                // BATTLE SCREEN
                else if (
                    current_screen ==
                    BATTLE_SCREEN
                    )
                {
                    if (
                        enemy->mouseInBox(
                            mouse_world
                        )
                        )
                    {
                        int damage =
                            player->getDamage();

                        enemy->takeDamage(
                            damage
                        );

                        std::cout
                            << "Boss hit for "
                            << damage
                            << "\n";

                        if (
                            enemy->isDead()
                            )
                        {
                            int points =
                                enemy->calculatePoints(
                                    player->getMoneyMultiplier()
                                );

                            player->addMoney(
                                points
                            );

                            std::cout
                                << "Boss defeated\n";

                            std::cout
                                << "Money earned: $"
                                << points
                                << "\n";

                            world_manager.removeObject(
                                enemy
                            );

                            shop->closeShop();

                            world_manager.addObject(
                                shop
                            );

                            world_manager.removeObject(
                                fight_button
                            );

                            current_screen =
                                SHOP_SCREEN;

                            std::cout
                                << "SHOP SCREEN\n";
                        }
                    }
                }

                // SHOP SCREEN
                else if (
                    current_screen ==
                    SHOP_SCREEN
                    )
                {
                    // SHOP CLOSED
                    if (
                        !shop->isOpen()
                        )
                    {
                        Box shop_box =
                            shop->getBox();

                        Vector shop_position =
                            shop->getPosition();

                        float left =
                            shop_position.getX() +
                            shop_box.getCorner().getX();

                        float right =
                            left +
                            shop_box.getHorizontal();

                        float top =
                            shop_position.getY() +
                            shop_box.getCorner().getY();

                        float bottom =
                            top +
                            shop_box.getVertical();

                        if (
                            mouse_world.getX() >= left &&
                            mouse_world.getX() <= right &&
                            mouse_world.getY() >= top &&
                            mouse_world.getY() <= bottom
                            )
                        {
                            shop->openShop();

                            world_manager.addObject(
                                fight_button
                            );

                            std::cout
                                << "SHOP OPENED\n";
                        }
                    }

                    // SHOP OPEN
                    else
                    {
                        shop->eventHandler(
                            &dragonfly_mouse_event
                        );

                        ShopUpgrade upgrade =
                            shop->getSelectedUpgrade();

                        if (
                            upgrade ==
                            ATTACK_UPGRADE
                            )
                        {
                            player->addAttackUpgrade();

                            std::cout
                                << "ATTACK UPGRADE PURCHASED\n";

                            std::cout
                                << "Damage: "
                                << player->getDamage()
                                << "\n";

                            shop->clearSelectedUpgrade();
                        }

                        else if (
                            upgrade ==
                            TIMER_UPGRADE
                            )
                        {
                            player->addTimerUpgrade();

                            std::cout
                                << "TIMER UPGRADE PURCHASED\n";

                            std::cout
                                << "Battle time: "
                                << player->getBattleTime() / 1000
                                << " seconds\n";

                            shop->clearSelectedUpgrade();
                        }

                        else if (
                            upgrade ==
                            DIFFICULTY_UPGRADE
                            )
                        {
                            player->addDifficultyUpgrade();

                            std::cout
                                << "DIFFICULTY UPGRADE PURCHASED\n";

                            std::cout
                                << "Boss health: "
                                << player->getEnemyHealth()
                                << "\n";

                            shop->clearSelectedUpgrade();
                        }

                        else if (
                            upgrade ==
                            MONEY_UPGRADE
                            )
                        {
                            player->addMoneyUpgrade();

                            std::cout
                                << "MONEY UPGRADE PURCHASED\n";

                            std::cout
                                << "Money multiplier: "
                                << player->getMoneyMultiplier()
                                << "\n";

                            shop->clearSelectedUpgrade();
                        }

                        // FIGHT BUTTON
                        fight_button->eventHandler(
                            &dragonfly_mouse_event
                        );

                        if (
                            fight_button->isClicked()
                            )
                        {
                            fight_button->clearClicked();

                            world_manager.removeObject(
                                fight_button
                            );

                            shop->closeShop();

                            world_manager.removeObject(
                                shop
                            );

                            world_manager.addObject(
                                enemy
                            );

                            current_screen =
                                BATTLE_SCREEN;

                            enemy->startTimer(
                                player->getEnemyHealth(),
                                player->getBattleTime()
                            );

                            std::cout
                                << "NEXT BATTLE STARTED\n";
                        }
                    }
                }
            }
        }

        // BATTLE TIMER
        if (
            current_screen ==
            BATTLE_SCREEN
            )
        {
            if (
                enemy->isTimeUp()
                )
            {
                std::cout
                    << "TIME UP\n";

                std::cout
                    << "YOU LOSE\n";

                break;
            }
        }

        // DRAW
        display_manager.drawString(
            Vector(40, 12),
            "TEST",
            CENTER_JUSTIFIED,
            WHITE
        );

        world_manager.draw();

        display_manager.swapBuffers();
    }

    resource_manager.shutDown();
    world_manager.shutDown();
    display_manager.shutDown();

    return 0;
}