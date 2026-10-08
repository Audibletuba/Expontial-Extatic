#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"

class Player : public Object
{
private:
    int m_money;

    int m_attack_upgrades;
    int m_timer_upgrades;
    int m_difficulty_upgrades;
    int m_money_upgrades;

public:
    Player(Vector position);

    // Money
    int getMoney() const;
    void addMoney(int amount);
    bool spendMoney(int amount);

    // Upgrades
    void addAttackUpgrade();
    void addTimerUpgrade();
    void addDifficultyUpgrade();
    void addMoneyUpgrade();

    int getAttackUpgrades() const;
    int getTimerUpgrades() const;
    int getDifficultyUpgrades() const;
    int getMoneyUpgrades() const;

    int getTotalUpgrades() const;

    // Player stats
    int getDamage() const;
    long getBattleTime() const;
    int getEnemyHealth() const;
    double getMoneyMultiplier() const;

	// Upgrade prices
    int getAttackPrice() const;
    int getTimerPrice() const;
    int getDifficultyPrice() const;
    int getMoneyPrice() const;


    // HUD

    int draw() override;
};

#endif