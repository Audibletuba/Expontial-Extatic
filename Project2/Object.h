#pragma once

#include "Vector.h"
#include "Event.h"
#include "Box.h"
#include "Animation.h"
#include <string>


const int MAX_ALTITUDE = 4;

enum Solidness
{
    SOLID,    // Object causes collisions and impedes.
    SOFT,    // Object causes collisions, but doesn't impede.
    SPECTRAL    // Object doesn't cause collisions.
};

class Object
{
private:
    Solidness m_solidness;

    Vector m_direction;
    float m_speed;
    Vector m_position;
    int m_type;
    int m_id;
    bool m_delete_flag;

    Box m_box; // Box for sprite boundary & collisions.
    Animation m_animation; // Animation associated with Object.

    // Static counter for unique Object IDs
    static int s_next_id;
    int m_altitude;

public:
    Object();
    Object(Vector position, int type = 0, int id = -1);
    virtual ~Object() = default;

    // soildiness state
    void setSolidness(Solidness new_solidness);
    Solidness getSolidness() const;
    bool isSolid() const;

    // Vector 
    void setVelocity(Vector new_velocity);
    Vector getVelocity() const;
    Vector predictPosition() const;
    virtual void update();

    // Position getter and setter
    Vector getPosition() const;
    void setPosition(Vector position);

    int m_width;
    int m_height;

    // Set Object's bounding box.
    void setBox(Box new_box);

    // Get Object's bounding box.
    Box getBox() const;

    // Type getter
    int getType() const;

    // ID getter
    int getID() const;

    // World management functions
    void addToWorld();
    void removeFromWorld();

    // Event handling
    virtual int eventHandler(const Event* event);

    // Delete flag getter and setter
    void setDeleteFlag(bool flag);
    bool getDeleteFlag() const;

    // Set altitude of Object.
    int setAltitude(int new_altitude);

    // Return altitude of Object.
    int getAltitude() const;


    // Set Sprite for this Object to animate.
 // Return 0 if ok, else -1.
    int setSprite(std::string sprite_label);

    // Set Animation for this Object to new one.
    // Set bounding box to size of associated Sprite.
    void setAnimation(Animation new_animation);

    // Get Animation for this Object.
    Animation getAnimation() const;

    // Draw Object Animation.
    // Return 0 if ok, else -1.
    virtual int draw();
    
};