#include "Player.h"
#include "DisplayManager.h"

#include <iostream>
#include <string>
#include <cmath>

Player::Player(Vector position)
    : Object(position)
{
    m_money = 0;

    m_attack_upgrades = 0;
    m_timer_upgrades = 0;
    m_difficulty_upgrades = 0;
    m_money_upgrades = 0;

    setSolidness(SPECTRAL);
    setAltitude(4);
}

int Player::getMoney() const
{
    return m_money;
}

void Player::addMoney(int amount)
{
    if (amount <= 0)
        return;

    m_money += amount;
}

bool Player::spendMoney(int amount)
{
    if (amount <= 0)
        return false;

    if (m_money < amount)
        return false;

    m_money -= amount;

    return true;
}

void Player::addAttackUpgrade()
{
    m_attack_upgrades++;
}

void Player::addTimerUpgrade()
{
    m_timer_upgrades++;
}

void Player::addDifficultyUpgrade()
{
    m_difficulty_upgrades++;
}

void Player::addMoneyUpgrade()
{
    m_money_upgrades++;
}

int Player::getAttackUpgrades() const
{
    return m_attack_upgrades;
}

int Player::getTimerUpgrades() const
{
    return m_timer_upgrades;
}

int Player::getDifficultyUpgrades() const
{
    return m_difficulty_upgrades;
}

int Player::getMoneyUpgrades() const
{
    return m_money_upgrades;
}

int Player::getTotalUpgrades() const
{
    return
        m_attack_upgrades +
        m_timer_upgrades +
        m_difficulty_upgrades +
        m_money_upgrades;
}

int Player::getDamage() const
{
    return static_cast<int>(
        10 * std::pow(
            1.25,
            m_attack_upgrades
        )
        );
}

long Player::getBattleTime() const
{
    return static_cast<long>(
        10000 * std::pow(
            1.15,
            m_timer_upgrades
        )
        );
}

int Player::getEnemyHealth() const
{
    return static_cast<int>(
        100 * std::pow(
            1.50,
            m_difficulty_upgrades
        )
        );
}

double Player::getMoneyMultiplier() const
{
    return std::pow(
        1.25,
        m_money_upgrades
    );
}

int Player::draw()
{
    DisplayManager& display_manager =
        DisplayManager::getInstance();

    sf::RenderWindow* window =
        display_manager.getWindow();

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

    sf::Text money_text(
        font,
        "MONEY: $" +
        std::to_string(m_money),
        22
    );

    sf::Text upgrades_text(
        font,
        "UPGRADES: " +
        std::to_string(getTotalUpgrades()),
        22
    );

    sf::Text damage_text(
        font,
        "DAMAGE: " +
        std::to_string(getDamage()),
        22
    );

    sf::Text difficulty_text(
        font,
        "DIFFICULTY: " +
        std::to_string(m_difficulty_upgrades),
        22
    );

    sf::Text time_text(
        font,
        "TIME: " +
        std::to_string(
            getBattleTime() / 1000
        ) +
        "s",
        22
    );

    money_text.setPosition(
        sf::Vector2f(25.0f, 10.0f)
    );

    upgrades_text.setPosition(
        sf::Vector2f(220.0f, 10.0f)
    );

    damage_text.setPosition(
        sf::Vector2f(410.0f, 10.0f)
    );

    difficulty_text.setPosition(
        sf::Vector2f(600.0f, 10.0f)
    );

    time_text.setPosition(
        sf::Vector2f(820.0f, 10.0f)
    );

    window->draw(money_text);
    window->draw(upgrades_text);
    window->draw(damage_text);
    window->draw(difficulty_text);
    window->draw(time_text);

    return 0;
}
int Player::getAttackPrice() const
{
    return static_cast<int>(
        50 * std::pow(
            1.25,
            m_attack_upgrades
        )
        );
}
int Player::getTimerPrice() const
{
    return static_cast<int>(
        50 * std::pow(
            1.5,
            m_timer_upgrades
        )
        );
}
int Player::getDifficultyPrice() const
{
    return static_cast<int>(
        50 * std::pow(
            2.0,
            m_difficulty_upgrades
        )
        );
}
int Player::getMoneyPrice() const
{
    return static_cast<int>(
        50 * std::pow(
            1.5,
            m_money_upgrades
        )
        );
}
