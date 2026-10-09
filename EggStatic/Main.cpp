#include "DisplayManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Shop.h"
#include "Button.h"
#include "MouseCursor.h"
#include "EventMouse.h"
#include "Music.h"
#include "Sound.h"
#include <string>

enum GameScreen { TITLE_SCREEN, BATTLE_SCREEN, SHOP_SCREEN, END_SCREEN };

int main()
{
    DisplayManager& display_manager = DisplayManager::getInstance();
    WorldManager& world_manager = WorldManager::getInstance();
    ResourceManager& resource_manager = ResourceManager::getInstance();

    display_manager.startUp();
    world_manager.startUp();
    resource_manager.startUp();

    world_manager.setBoundary(Box(Vector(0, 0), 80, 24));
    world_manager.setView(Box(Vector(0, 0), 80, 24));

    resource_manager.loadSprite("Sprites/shop.txt", "shop");
    resource_manager.loadSprite("Sprites/attack.txt", "attack");
    resource_manager.loadSprite("Sprites/title.txt", "title");
    resource_manager.loadSprite("Sprites/time.txt", "timer");
    resource_manager.loadSprite("Sprites/difficulty.txt", "difficulty");
    resource_manager.loadSprite("Sprites/money.txt", "money");
    resource_manager.loadSprite("Sprites/enemy.txt", "enemy");
    resource_manager.loadSprite("Sprites/play.txt", "play");
    resource_manager.loadSprite("Sprites/fight.txt", "fight");
    resource_manager.loadSprite("Sprites/restart.txt", "restart");
    resource_manager.loadSprite("Sprites/quit.txt", "quit");
    resource_manager.loadSprite("Sprites/pan.txt", "pan");

    // Background music
    resource_manager.loadMusic("Sounds/music_Title.wav", "title_music");
    resource_manager.loadMusic("Sounds/music_Battle.wav", "battle_music");
    resource_manager.loadMusic("Sounds/music_Shop.wav", "shop_music");

    // Sound effects
    resource_manager.loadSound("Sounds/purchase.wav", "purchase");
    resource_manager.loadSound("Sounds/defeat_sound.wav", "boss_defeat");
    resource_manager.loadSound("Sounds/shopfail_sound.wav", "noMoney");

    std::string current_music;
    auto playMusic = [&](const std::string& label)
        {
            if (current_music == label)
                return;

            if (!current_music.empty())
            {
                Music* old_music = resource_manager.getMusic(current_music);
                if (old_music != nullptr)
                    old_music->stop();
            }

            Music* music = resource_manager.getMusic(label);
            if (music != nullptr)
            {
                music->play(true);
                current_music = label;
            }
            else
            {
                current_music.clear();
            }
        };

    auto stopMusic = [&]()
        {
            if (!current_music.empty())
            {
                Music* music = resource_manager.getMusic(current_music);
                if (music != nullptr)
                    music->stop();
            }
            current_music.clear();
        };

    auto playSound = [&](const std::string& label)
        {
            Sound* sound = resource_manager.getSound(label);
            if (sound != nullptr)
                sound->play();
        };

    Player* player = new Player(Vector(40, 0));
    Enemy* enemy = new Enemy(Vector(40, 12), player->getEnemyHealth());
    Shop* shop = new Shop(Vector(40, 12));
    shop->setPlayer(player);

    Button* fight_button = new Button(Vector(40, 21), "fight");
    Object* title = new Object(Vector(40, 10));
    title->setSprite("title");
    title->setAltitude(1);
    Button* play_button = new Button(Vector(40, 13), "play");
    play_button->setAltitude(2);

    Button* restart_button = new Button(Vector(30, 19), "restart");
    Button* quit_button = new Button(Vector(50, 19), "quit");
    MouseCursor* mouse_cursor = new MouseCursor(Vector(40, 12));

    GameScreen current_screen = TITLE_SCREEN;
    Vector mouse_world(40, 12);
    int total_score = 0;

    world_manager.addObject(player);
    world_manager.addObject(play_button);
    world_manager.addObject(title);
    world_manager.addObject(mouse_cursor);

    playMusic("title_music");

    while (display_manager.getWindow()->isOpen())
    {
        sf::Vector2i mouse_pixel = sf::Mouse::getPosition(*display_manager.getWindow());
        float world_x = (static_cast<float>(mouse_pixel.x) / 1024.0f) * 80.0f;
        float world_y = (static_cast<float>(mouse_pixel.y) / 768.0f) * 24.0f;
        mouse_world = Vector(world_x, world_y);
        mouse_cursor->setPosition(mouse_world);

        while (auto event = display_manager.getWindow()->pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                stopMusic();
                display_manager.getWindow()->close();
            }

            if (auto mouse_event = event->getIf<sf::Event::MouseButtonPressed>())
            {
                EventMouse dragonfly_mouse_event;
                dragonfly_mouse_event.setMouseAction(CLICKED);
                dragonfly_mouse_event.setMouseXY(mouse_world);

                if (mouse_event->button == sf::Mouse::Button::Left)
                {
                    dragonfly_mouse_event.setMouseButton(Mouse::LEFT);

                    if (current_screen == TITLE_SCREEN)
                    {
                        play_button->eventHandler(&dragonfly_mouse_event);
                        if (play_button->isClicked())
                        {
                            play_button->clearClicked();
                            world_manager.removeObject(play_button);
                            world_manager.removeObject(title);
                            world_manager.addObject(enemy);
                            current_screen = BATTLE_SCREEN;
                            enemy->startTimer(player->getEnemyHealth(), player->getBattleTime());
                            playMusic("battle_music");
                        }
                    }
                    else if (current_screen == BATTLE_SCREEN)
                    {
                        if (enemy->mouseInBox(mouse_world))
                        {
                            int damage = player->getDamage();
                            enemy->takeDamage(damage);

                            if (enemy->isDead())
                            {
                                int points = enemy->calculatePoints(player->getMoneyMultiplier());
                                player->addMoney(points);
                                player->addEggsBeat();
                                total_score += points;
                                playSound("boss_defeat");

                                world_manager.removeObject(enemy);
                                shop->closeShop();
                                world_manager.addObject(shop);
                                world_manager.removeObject(fight_button);
                                current_screen = SHOP_SCREEN;
                                playMusic("shop_music");
                            }
                        }
                    }
                    else if (current_screen == SHOP_SCREEN)
                    {
                        if (shop->isOpen())
                        {
                            shop->eventHandler(&dragonfly_mouse_event);
                            ShopUpgrade upgrade = shop->getSelectedUpgrade();

                            if (upgrade == ATTACK_UPGRADE)
                            {
                                int price = player->getAttackPrice();
                                if (player->spendMoney(price))
                                {
                                    player->addAttackUpgrade();
                                    playSound("purchase");
                                }
                                else
                                {
                                    playSound("noMoney");
                                }
                                shop->clearSelectedUpgrade();
                            }
                            else if (upgrade == TIMER_UPGRADE)
                            {
                                int price = player->getTimerPrice();
                                if (player->spendMoney(price))
                                {
                                    player->addTimerUpgrade();
                                    playSound("purchase");
                                }
                                else
                                {
                                    playSound("noMoney");
                                }
                                shop->clearSelectedUpgrade();
                            }
                            else if (upgrade == DIFFICULTY_UPGRADE)
                            {
                                int price = player->getDifficultyPrice();
                                if (player->spendMoney(price))
                                {
                                    player->addDifficultyUpgrade();
                                    playSound("purchase");
                                }
                                else
                                {
                                    playSound("noMoney");
                                }
                                shop->clearSelectedUpgrade();
                            }
                            else if (upgrade == MONEY_UPGRADE)
                            {
                                int price = player->getMoneyPrice();
                                if (player->spendMoney(price))
                                {
                                    player->addMoneyUpgrade();
                                    playSound("purchase");
                                }
                                else
                                {
                                    playSound("noMoney");
                                }
                                shop->clearSelectedUpgrade();
                            }

                            fight_button->eventHandler(&dragonfly_mouse_event);
                            if (fight_button->isClicked())
                            {
                                fight_button->clearClicked();
                                world_manager.removeObject(fight_button);
                                shop->closeShop();
                                world_manager.removeObject(shop);
                                world_manager.addObject(enemy);
                                current_screen = BATTLE_SCREEN;
                                enemy->startTimer(player->getEnemyHealth(), player->getBattleTime());
                                playMusic("battle_music");
                            }
                        }
                    }
                    else if (current_screen == END_SCREEN)
                    {
                        restart_button->eventHandler(&dragonfly_mouse_event);
                        quit_button->eventHandler(&dragonfly_mouse_event);

                        if (restart_button->isClicked())
                        {
                            restart_button->clearClicked();
                            quit_button->clearClicked();
                            player->reset();
                            total_score = 0;
                            shop->closeShop();

                            world_manager.removeObject(restart_button);
                            world_manager.removeObject(quit_button);
                            world_manager.removeObject(shop);
                            world_manager.removeObject(enemy);

                            world_manager.addObject(title);
                            world_manager.addObject(play_button);
                            current_screen = TITLE_SCREEN;
                            playMusic("title_music");
                        }
                        else if (quit_button->isClicked())
                        {
                            quit_button->clearClicked();
                            restart_button->clearClicked();
                            stopMusic();
                            display_manager.getWindow()->close();
                        }
                    }
                }
                else if (mouse_event->button == sf::Mouse::Button::Right)
                {
                    dragonfly_mouse_event.setMouseButton(Mouse::RIGHT);

                    if (current_screen == SHOP_SCREEN && !shop->isOpen())
                    {
                        Box shop_box = shop->getBox();
                        Vector shop_position = shop->getPosition();

                        float left = shop_position.getX() + shop_box.getCorner().getX();
                        float right = left + shop_box.getHorizontal();
                        float top = shop_position.getY() + shop_box.getCorner().getY();
                        float bottom = top + shop_box.getVertical();

                        if (mouse_world.getX() >= left && mouse_world.getX() <= right &&
                            mouse_world.getY() >= top && mouse_world.getY() <= bottom)
                        {
                            shop->openShop();
                            world_manager.addObject(fight_button);
                        }
                    }
                }
            }
        }

        if (current_screen == BATTLE_SCREEN && enemy->isTimeUp())
        {
            world_manager.removeObject(enemy);
            world_manager.addObject(restart_button);
            world_manager.addObject(quit_button);
            current_screen = END_SCREEN;
            stopMusic();
        }

        display_manager.getWindow()->clear();
        world_manager.draw();

        if (current_screen == END_SCREEN)
        {
			playMusic("title_music");
            display_manager.drawString(Vector(40, 3), "GAME OVER", CENTER_JUSTIFIED, RED);
            display_manager.drawString(Vector(40, 6), "EGGS CRACKED: " + std::to_string(player->getEggsBeat()), CENTER_JUSTIFIED, WHITE);
            display_manager.drawString(Vector(40, 9), "UPGRADES", CENTER_JUSTIFIED, YELLOW);
            display_manager.drawString(Vector(40, 10), "ATTACK: " + std::to_string(player->getAttackUpgrades()), CENTER_JUSTIFIED, WHITE);
            display_manager.drawString(Vector(40, 11), "TIMER: " + std::to_string(player->getTimerUpgrades()), CENTER_JUSTIFIED, WHITE);
            display_manager.drawString(Vector(40, 12), "DIFFICULTY: " + std::to_string(player->getDifficultyUpgrades()), CENTER_JUSTIFIED, WHITE);
            display_manager.drawString(Vector(40, 13), "MONEY: " + std::to_string(player->getMoneyUpgrades()), CENTER_JUSTIFIED, WHITE);
            display_manager.drawString(Vector(40, 15), "TOTAL UPGRADES: " + std::to_string(player->getTotalUpgrades()), CENTER_JUSTIFIED, YELLOW);
            display_manager.drawString(Vector(40, 16), "TOTAL SCORE: " + std::to_string(total_score), CENTER_JUSTIFIED, GREEN);
        }

        display_manager.swapBuffers();
    }

    stopMusic();
    resource_manager.shutDown();
    world_manager.shutDown();
    display_manager.shutDown();
    return 0;
}
