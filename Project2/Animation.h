#pragma once

// System includes.
#include <string>

// Engine includes.
#include "Sprite.h"
#include "Vector.h"
#include "Box.h"

class Animation
{
private:
    Sprite* m_p_sprite;        // Sprite associated with Animation.
    std::string m_name;        // Sprite name in ResourceManager.
    int m_index;               // Current Sprite frame index.
    int m_slowdown_count;      // Slowdown counter.

public:
    // Animation constructor.
    Animation();

    // Set associated Sprite to new one.
    // Sprite is managed by ResourceManager.
    // Set Sprite index to 0 (first frame).
    void setSprite(Sprite* p_new_sprite);

    // Return associated Sprite.
    Sprite* getSprite() const;

    // Set Sprite name.
    void setName(std::string new_name);

    // Get Sprite name.
    std::string getName() const;

    // Set current frame index.
    void setIndex(int new_index);

    // Get current frame index.
    int getIndex() const;

    // Set slowdown count (-1 means stop animation).
    void setSlowdownCount(int new_slowdown_count);

    // Get slowdown count.
    int getSlowdownCount() const;

    // Draw current frame.
    // Accounts for slowdown and advances frames.
    int draw(Vector position);

    // Get bounding box of associated Sprite.
    Box getBox() const;
};
