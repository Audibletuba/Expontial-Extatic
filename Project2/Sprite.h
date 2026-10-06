#pragma once

#include <string>
#include "Frame.h"



class Sprite
{
private:
    int m_width;                 // Sprite width.
    int m_height;                // Sprite height.
    int m_max_frame_count;       // Max number frames sprite can have.
    int m_frame_count;           // Actual number frames sprite has.
    Color m_color;               // Optional color for entire sprite.
    int m_slowdown;              // Animation slowdown.
    Frame* m_frame;              // Array of frames.
    std::string m_label;         // Text label to identify sprite.

    Sprite();                    // Sprite always has one arg, frame count.

public:
    // Destroy sprite, deleting any allocated frames.
    ~Sprite();

    // Create sprite with indicated maximum number of frames.
    Sprite(int max_frames);

    // Set width of sprite.
    void setWidth(int new_width);

    // Get width of sprite.
    int getWidth() const;

    // Set height of sprite.
    void setHeight(int new_height);

    // Get height of sprite.
    int getHeight() const;

    // Set sprite color.
    void setColor(Color new_color);

    // Get sprite color.
    Color getColor() const;

    // Get total count of frames in sprite.
    int getFrameCount() const;

    // Add frame to sprite.
    int addFrame(Frame new_frame);

    // Get sprite frame indicated by number.
    Frame getFrame(int frame_number) const;

    // Set label associated with sprite.
    void setLabel(std::string new_label);

    // Get label associated with sprite.
    std::string getLabel() const;

    // Set animation slowdown value.
    void setSlowdown(int new_sprite_slowdown);

    // Get animation slowdown value.
    int getSlowdown() const;

    // Draw indicated frame centered at position.
    // return 0 fi true else -1
    // top left (0,0)

    int draw(int frame_number, Vector position) const;
};


