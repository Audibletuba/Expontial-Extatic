#include "Button.h"

Button::Button(Vector position, const std::string& sprite)
    : Object(position)
{
    m_clicked = false;

    setSolidness(SPECTRAL);
    setSprite(sprite);
}

int Button::eventHandler(const Event* event)
{
    const EventMouse* mouse_event =
        dynamic_cast<const EventMouse*>(event);

    if (mouse_event == nullptr)
        return 0;

    if (mouse_event->getMouseAction() != CLICKED)
        return 0;

    if (mouse_event->getMouseButton() != Mouse::LEFT)
        return 0;

    Vector mouse_position = mouse_event->getMouseXY();

    Box box = getBox();

    // Object boxes are relative to the object's position.
    Vector world_position = getPosition();

    float left =
        world_position.getX() + box.getCorner().getX();

    float right =
        left + box.getHorizontal();

    float top =
        world_position.getY() + box.getCorner().getY();

    float bottom =
        top + box.getVertical();

    if (mouse_position.getX() >= left &&
        mouse_position.getX() <= right &&
        mouse_position.getY() >= top &&
        mouse_position.getY() <= bottom)
    {
        m_clicked = true;
    }

    return 0;
}

int Button::draw()
{
    Object::draw();
    return 0;
}

bool Button::isClicked() const
{
    return m_clicked;
}

void Button::clearClicked()
{
    m_clicked = false;
}