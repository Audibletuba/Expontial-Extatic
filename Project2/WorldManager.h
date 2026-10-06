#pragma once

#include "Manager.h"
#include "Event.h"
#include "Box.h"
#include "ObjectList.h"

class WorldManager : public Manager
{
private:
    ObjectList m_object_list;
    Object* p_view_following; // Object view is following.

    // Singleton: private constructor
    WorldManager();

    Box m_boundary; // World boundary.
    Box m_view;     // Player view of game world.

public:
    static WorldManager& getInstance();

    // Move Object to a new position.
    int moveObject(Object* p_o, Vector where);

    // startup shutdown functionsS
    void startUp();
    void shutDown();
    // draw
    void draw();

    // add and remove from world
    void addObject(Object* object);
    void removeObject(Object* object);

    // object list
    ObjectList& getAllObjects();

    // deletion process
    void markForDelete(Object* object);
    void processDeletes();

    ObjectList getCollisions(const Object* p_o, Vector where);
   
    // Set game world boundary.
    void setBoundary(Box new_boundary);

    // Get game world boundary.
    Box getBoundary() const;

    // Set player view of game world.
    void setView(Box new_view);

    // Get player view of game world.
    Box getView() const;

    // Set view to center window on position view_pos.
// View edge will not go beyond world boundary.
    void setViewPosition(Vector view_pos);

    // Set view to center window on Object.
    // Set to NULL to stop following.
    // If p_new_view_following not legit, return -1 else return 0.
    int setViewFollowing(Object* p_new_view_following);

};
