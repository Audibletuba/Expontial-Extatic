#ifndef SHOP_H
#define SHOP_H

#include "Object.h"
#include "Animation.h"
#include "Box.h"
#include "EventMouse.h"

enum ShopUpgrade
{
    NO_UPGRADE,
    ATTACK_UPGRADE,
    TIMER_UPGRADE,
    DIFFICULTY_UPGRADE,
    MONEY_UPGRADE
};

class Shop : public Object
{
private:
    bool m_open;
    ShopUpgrade m_selected_upgrade;

    Animation m_attack_animation;
    Animation m_timer_animation;
    Animation m_difficulty_animation;
    Animation m_money_animation;

    Box m_attack_box;
    Box m_timer_box;
    Box m_difficulty_box;
    Box m_money_box;

    Vector m_attack_position;
    Vector m_timer_position;
    Vector m_difficulty_position;
    Vector m_money_position;

    void setupUpgrade(
        Animation& animation,
        Box& box,
        const std::string& sprite_label,
        Vector position
    );

    bool mouseInBox(Vector mouse_world, Box box);

public:
    Shop(Vector position);

    int eventHandler(const Event* event) override;
    int draw() override;

    bool isOpen() const;

    void openShop();
    void closeShop();

    bool mouseInBox(Vector mouse_world, Box box, Vector position);

    ShopUpgrade getSelectedUpgrade() const;

    void clearSelectedUpgrade();
};

#endif