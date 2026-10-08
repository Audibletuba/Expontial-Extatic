#ifndef ENEMY_H
#define ENEMY_H

#include "Object.h"
#include "Clock.h"

class Enemy : public Object
{
private:
    int m_health;
    int m_max_health;

    int m_points;

    Clock m_clock;
    long m_round_time;

public:
    Enemy(Vector position, int health);

    void takeDamage(int damage);

    int getHealth() const;
    int getMaxHealth() const;

    bool isDead() const;

    bool mouseInBox(Vector mouse_world);

    void startTimer(
        int enemy_health,
        long battle_time
    );

    bool isTimeUp();

    int calculatePoints(
        double money_multiplier
    );

    int getPoints() const;

    int draw() override;
};

#endif