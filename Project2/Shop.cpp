#include "Shop.h"
#include "ResourceManager.h"

#include <iostream>

Shop::Shop(Vector position)
    : Object(position)
{
    m_open = false;
    m_selected_upgrade = NO_UPGRADE;

    setSolidness(SPECTRAL);
    setSprite("shop");

    // Keep the current upgrade positions
    m_attack_position =
        Vector(
            position.getX() - 10,
            position.getY() - 5
        );

    m_timer_position =
        Vector(
            position.getX() + 30,
            position.getY() - 5
        );

    m_difficulty_position =
        Vector(
            position.getX() + 10,
            position.getY() - 5
        );

    m_money_position =
        Vector(
            position.getX() - 30,
            position.getY() - 5
        );

    setupUpgrade(
        m_attack_animation,
        m_attack_box,
        "attack",
        m_attack_position
    );

    setupUpgrade(
        m_timer_animation,
        m_timer_box,
        "timer",
        m_timer_position
    );

    setupUpgrade(
        m_difficulty_animation,
        m_difficulty_box,
        "difficulty",
        m_difficulty_position
    );

    setupUpgrade(
        m_money_animation,
        m_money_box,
        "money",
        m_money_position
    );
}

void Shop::setupUpgrade(
    Animation& animation,
    Box& box,
    const std::string& sprite_label,
    Vector position
)
{
    ResourceManager& resource_manager =
        ResourceManager::getInstance();

    Sprite* sprite =
        resource_manager.getSprite(
            sprite_label
        );

    if (sprite == nullptr)
    {
        std::cout
            << "Failed to get sprite: "
            << sprite_label
            << "\n";

        return;
    }

    animation.setSprite(sprite);

    box.setCorner(
        Vector(
            -static_cast<float>(sprite->getWidth()) / 2.0f,
            -static_cast<float>(sprite->getHeight()) / 2.0f
        )
    );

    box.setHorizontal(
        static_cast<float>(sprite->getWidth())
    );

    box.setVertical(
        static_cast<float>(sprite->getHeight())
    );
}

bool Shop::mouseInBox(
    Vector mouse_world,
    Box box
)
{
    Vector position =
        getPosition();

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

int Shop::eventHandler(const Event* event)
{
    const EventMouse* mouse_event =
        dynamic_cast<const EventMouse*>(event);

    if (mouse_event == nullptr)
        return 0;

    if (
        mouse_event->getMouseAction() !=
        CLICKED
        )
        return 0;

    if (
        mouse_event->getMouseButton() !=
        Mouse::LEFT
        )
        return 0;

    if (!m_open)
        return 0;

    Vector mouse_position =
        mouse_event->getMouseXY();

    // ATTACK
    float attack_left =
        m_attack_position.getX() +
        m_attack_box.getCorner().getX();

    float attack_right =
        attack_left +
        m_attack_box.getHorizontal();

    float attack_top =
        m_attack_position.getY() +
        m_attack_box.getCorner().getY();

    float attack_bottom =
        attack_top +
        m_attack_box.getVertical();

    if (
        mouse_position.getX() >= attack_left &&
        mouse_position.getX() <= attack_right &&
        mouse_position.getY() >= attack_top &&
        mouse_position.getY() <= attack_bottom
        )
    {
        m_selected_upgrade =
            ATTACK_UPGRADE;

        std::cout
            << "Attack upgrade clicked\n";

        return 0;
    }

    // TIMER
    float timer_left =
        m_timer_position.getX() +
        m_timer_box.getCorner().getX();

    float timer_right =
        timer_left +
        m_timer_box.getHorizontal();

    float timer_top =
        m_timer_position.getY() +
        m_timer_box.getCorner().getY();

    float timer_bottom =
        timer_top +
        m_timer_box.getVertical();

    if (
        mouse_position.getX() >= timer_left &&
        mouse_position.getX() <= timer_right &&
        mouse_position.getY() >= timer_top &&
        mouse_position.getY() <= timer_bottom
        )
    {
        m_selected_upgrade =
            TIMER_UPGRADE;

        std::cout
            << "Timer upgrade clicked\n";

        return 0;
    }

    // DIFFICULTY
    float difficulty_left =
        m_difficulty_position.getX() +
        m_difficulty_box.getCorner().getX();

    float difficulty_right =
        difficulty_left +
        m_difficulty_box.getHorizontal();

    float difficulty_top =
        m_difficulty_position.getY() +
        m_difficulty_box.getCorner().getY();

    float difficulty_bottom =
        difficulty_top +
        m_difficulty_box.getVertical();

    if (
        mouse_position.getX() >= difficulty_left &&
        mouse_position.getX() <= difficulty_right &&
        mouse_position.getY() >= difficulty_top &&
        mouse_position.getY() <= difficulty_bottom
        )
    {
        m_selected_upgrade =
            DIFFICULTY_UPGRADE;

        std::cout
            << "Difficulty upgrade clicked\n";

        return 0;
    }

    // MONEY
    float money_left =
        m_money_position.getX() +
        m_money_box.getCorner().getX();

    float money_right =
        money_left +
        m_money_box.getHorizontal();

    float money_top =
        m_money_position.getY() +
        m_money_box.getCorner().getY();

    float money_bottom =
        money_top +
        m_money_box.getVertical();

    if (
        mouse_position.getX() >= money_left &&
        mouse_position.getX() <= money_right &&
        mouse_position.getY() >= money_top &&
        mouse_position.getY() <= money_bottom
        )
    {
        m_selected_upgrade =
            MONEY_UPGRADE;

        std::cout
            << "Money upgrade clicked\n";

        return 0;
    }

    return 0;
}

int Shop::draw()
{
    Object::draw();

    if (!m_open)
        return 0;

    m_attack_animation.draw(
        m_attack_position
    );

    m_timer_animation.draw(
        m_timer_position
    );

    m_difficulty_animation.draw(
        m_difficulty_position
    );

    m_money_animation.draw(
        m_money_position
    );

    return 0;
}

bool Shop::isOpen() const
{
    return m_open;
}

void Shop::openShop()
{
    m_open = true;

    m_selected_upgrade =
        NO_UPGRADE;

    std::cout
        << "SHOP OPENED\n";
}

void Shop::closeShop()
{
    m_open = false;

    m_selected_upgrade =
        NO_UPGRADE;

    std::cout
        << "SHOP CLOSED\n";
}

ShopUpgrade Shop::getSelectedUpgrade() const
{
    return m_selected_upgrade;
}

void Shop::clearSelectedUpgrade()
{
    m_selected_upgrade =
        NO_UPGRADE;
}