#include "Enemy.h"
#include "DisplayManager.h"

#include <iostream>
#include <string>

Enemy::Enemy(Vector position, int health)
    : Object(position)
{
    m_max_health = health;
    m_health = health;

    m_points = 0;

    m_round_time = 10000;

    setSolidness(SPECTRAL);
    setSprite("enemy");
}

void Enemy::takeDamage(int damage)
{
    if (damage <= 0)
        return;

    m_health -= damage;

    if (m_health < 0)
        m_health = 0;
}

int Enemy::getHealth() const
{
    return m_health;
}

int Enemy::getMaxHealth() const
{
    return m_max_health;
}

bool Enemy::isDead() const
{
    return m_health <= 0;
}

bool Enemy::mouseInBox(Vector mouse_world)
{
    Box box = getBox();
    Vector position = getPosition();

    float left =
        position.getX() +
        box.getCorner().getX();

    float right =
        left +
        box.getHorizontal();

    float top =
        position.getY() +
        box.getCorner().getY();

    float bottom =
        top +
        box.getVertical();

    return
        mouse_world.getX() >= left &&
        mouse_world.getX() <= right &&
        mouse_world.getY() >= top &&
        mouse_world.getY() <= bottom;
}

void Enemy::startTimer(
    int enemy_health,
    long battle_time
)
{
    m_max_health = enemy_health;
    m_health = m_max_health;

    m_round_time = battle_time;

    m_points = 0;

    m_clock.restart();
}

bool Enemy::isTimeUp()
{
    return
        m_clock.getElapsedTime() >=
        m_round_time;
}

int Enemy::calculatePoints(
    double money_multiplier
)
{
    long elapsed =
        m_clock.getElapsedTime();

    if (elapsed >= m_round_time)
    {
        m_points = 0;
        return m_points;
    }

    long remaining =
        m_round_time - elapsed;

    int base_points =
        static_cast<int>(
            (100.0 * remaining) /m_round_time);

    m_points =
        static_cast<int>(base_points * money_multiplier) + 50*static_cast<int>(money_multiplier);

    return m_points;
}

int Enemy::getPoints() const
{
    return m_points;
}

int Enemy::draw()
{
    // Draw the egg.
    Object::draw();

    DisplayManager& display_manager =
        DisplayManager::getInstance();

    sf::RenderWindow* window =
        display_manager.getWindow();

    // Get remaining time.
    long elapsed =
        m_clock.getElapsedTime();

    long remaining =
        m_round_time - elapsed;

    if (remaining < 0)
        remaining = 0;

    int remaining_seconds =
        static_cast<int>(
            remaining / 1000
            );

    // Load font once.
    static sf::Font font;
    static bool font_loaded = false;

    if (!font_loaded)
    {
        if (!font.openFromFile("df-font.ttf"))
        {
            std::cout
                << "Failed to load df-font.ttf\n";

            return 0;
        }

        font_loaded = true;
    }

    // Boss HP.
    sf::Text health_text(
        font,
        "BOSS HP: " +
        std::to_string(m_health) +
        " / " +
        std::to_string(m_max_health),
        24
    );

    // Battle timer.
    sf::Text timer_text(
        font,
        "BATTLE TIME: " +
        std::to_string(remaining_seconds),
        24
    );

    // Move battle HUD below the Player HUD.
    health_text.setPosition(
        sf::Vector2f(
            50.0f,
            700.0f
        )
    );

    timer_text.setPosition(
        sf::Vector2f(
            700.0f,
            700.0f
        )
    );

    window->draw(health_text);
    window->draw(timer_text);

    return 0;
}