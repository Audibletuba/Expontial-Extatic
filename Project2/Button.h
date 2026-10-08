#ifndef BUTTON_H
#define BUTTON_H

#include "Object.h"
#include "EventMouse.h"

class Button : public Object
{
private:
    bool m_clicked;

public:
    Button(Vector position, const std::string& sprite);

    int eventHandler(const Event* event) override;
    int draw() override;

    bool isClicked() const;
    void clearClicked();
};

#endif#

